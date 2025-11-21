#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    clients.append(socket);
    _pendingUsernameSockets.insert(socket);

    qDebug() << "Client connected:" << socketDescriptor;

    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray data = socket->readAll();
        qDebug() << "Raw received:" << data;

        // Check if username is not set yet:
        if (_pendingUsernameSockets.contains(socket)) {
            QString msg = QString::fromUtf8(data).trimmed();

            if (msg.startsWith("USERNAME:")) {
                QString username = msg.mid(QString("USERNAME:").length()).trimmed();
                _socket_username_map[socket] = username;
                _pendingUsernameSockets.remove(socket);

                qDebug() << "Username registered:" << username;
            } else {
                qDebug() << "Error: First message must contain username!";
            }

            return; // Do not broadcast username message
        }

        // After username is registered → normal messages:
        broadcastMessage(data, socket);
    });

    connect(socket, &QTcpSocket::disconnected, [this, socket]() {
        clients.removeOne(socket);

        _socket_username_map.remove(socket);
        _pendingUsernameSockets.remove(socket);

        socket->deleteLater();
        qDebug() << "Client disconnected";
    });
}

void Server::broadcastMessage(const QByteArray &message, QTcpSocket *sender)
{
    for (QTcpSocket* client : clients)
    {
        if (client != sender)
        {
            client->write(message);
        }
    }
}

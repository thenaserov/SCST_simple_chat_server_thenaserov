#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}


void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    clients.append(socket);

    qDebug() << "Client connected:" << socketDescriptor;

    connect(socket, &QTcpSocket::readyRead, [this, socket]() {
        QByteArray data = socket->readAll();
        qDebug() << "Received:" << data;

        broadcastMessage(data, socket);
    });

    connect(socket, &QTcpSocket::disconnected, [this, socket]() {
        clients.removeOne(socket);
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

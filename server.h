#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QList<QTcpSocket*> clients;
    QMap<QTcpSocket*, QString> _socket_username_map;
    QSet<QTcpSocket*> _pendingUsernameSockets;
    void broadcastMessage(const QByteArray& message, QTcpSocket* sender);

signals:

};

#endif // SERVER_H

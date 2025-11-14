#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    if (!server.listen(QHostAddress::LocalHost, 5000)) {
        qDebug() << "Failed to start server";
        return 1;
    }

    qDebug() << "Server started on port 5000";

    return a.exec();
}

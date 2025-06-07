#include "listener.h"
#include "pathgetter.h"


void Listener::on()
{
    server = new TcpServer(6111);
    connect(server, SIGNAL(signalDataReceived(QByteArray)),
            this, SLOT(handleCommand(QByteArray)));
    server->up();
}

void Listener::handleCommand(QByteArray data)
{
    QString command = QString(data);
    QStringList commandArgs = command.split("#");

    int name = 0, body = 1;

    if (QString::compare(commandArgs[name], QString("Path")) == 0)
    {
        PathGetter getter;
        QVector<int> path = getter.get(commandArgs[body]);
        emit pathReceived(path);
    }
}

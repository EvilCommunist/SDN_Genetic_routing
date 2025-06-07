#include "tcpserver.h"
#include <QTcpSocket>
#include <QDataStream>

TcpServer::TcpServer(int listenedPort) : online(true)
{
    core = new QTcpServer(this);
    if (!core->listen(QHostAddress::Any, listenedPort))
    {
        core->close();
        return;
    }
    connect(core, SIGNAL(newConnection()),
            this, SLOT(handleNewConnection()));
}

TcpServer::~TcpServer()
{
    core->close();
    delete core;
}

void TcpServer::up()
{
    start();
}

void TcpServer::handleNewConnection()
{
    auto *client = core->nextPendingConnection();
    connect(client, SIGNAL(disconnected()),
            client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()),
            this, SLOT(readData()));
}

void TcpServer::readData()
{
    auto *client = (QTcpSocket*)sender();
    QByteArray data;
    data.append(client->readAll());
    emit signalDataReceived(data);
}

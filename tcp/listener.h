#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include "tcpserver.h"

class Listener : public QObject
{
    Q_OBJECT
private:
    TcpServer *server;

public slots:
    void on();
    void handleCommand(QByteArray data);

signals:
    void pathReceived(QVector<int> path);
    void pathsReceived(QVector<QVector<int>> paths);
};

#endif // LISTENER_H

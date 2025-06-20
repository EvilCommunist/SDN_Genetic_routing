#include "mainwindow.h"

#include <QApplication>
#include "tcp/listener.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Listener listener;

    QObject::connect(&listener, SIGNAL(pathReceived(QVector<int>)), &w, SLOT(visualizePath(QVector<int>)));
    QObject::connect(&listener, SIGNAL(pathsReceived(QVector<QVector<int>>)), &w, SLOT(visualizePaths(QVector<QVector<int>>)));

    w.setWindowTitle("G_SDN");
    w.setWindowIcon(QIcon(":/imgs/DNA.png"));
    w.show();
    listener.on();
    return a.exec();
}

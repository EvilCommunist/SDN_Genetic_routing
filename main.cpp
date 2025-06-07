#include "mainwindow.h"

#include <QApplication>
#include "tcp/listener.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Listener listener;

    QObject::connect(&listener, SIGNAL(pathReceived(QVector<int>)), &w, SLOT(visualizePath(QVector<int>)));

    w.setWindowTitle("G_SDN");
    w.show();
    listener.on();
    return a.exec();
}

#include "host.h"
#include "hostdialog.h"
#include <QStyleOptionGraphicsItem>

Host::Host(QPoint position, int number, QGraphicsItem *parent)
    : NetNode(DeviceType::HOST, parent){
    setName(QString("h%0").arg(number));
    setIpAddr(QString("10.0.0.%0").arg(number));
    setMacAddr(QString("00:00:00:00:00:%0").arg(number, 2, 10, QChar('0')));

    setPos(position);
}

QRectF Host::boundingRect() const{
    return QRectF(0, 0, 70, 70);
}

void Host::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawRect(boundingRect().adjusted(-2, -2, 2, 2));
    }
    painter->setPen(Qt::black);
    painter->setBrush(Qt::lightGray);
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), Qt::AlignCenter, getName());
}

void Host::configure(){
    HostDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        update();
    }
}

QString Host::getMacAddr() const { return macAddr; }
void Host::setMacAddr(const QString &mac){ macAddr = mac; update(); }
QString Host::getIpAddr() const { return ipAddr; }
void Host::setIpAddr(const QString &ip) { ipAddr = ip; update(); }

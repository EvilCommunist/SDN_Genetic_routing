#include "host.h"
#include "hostdialog.h"
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>

Host::Host(QPoint position, int number, QGraphicsItem *parent)
    : NetNode(DeviceType::HOST, parent){
    setName(QString("h%0").arg(number));
    setIpAddr(QString("10.0.0.%0").arg(number));
    setMacAddr(QString("00:00:00:00:00:%0").arg(number, 2, 10, QChar('0')));

    setPos(position);
}

QRectF Host::boundingRect() const{
    return QRectF(-SIZE/2 - PADDING, -SIZE/2 - PADDING,
                 SIZE + 2*PADDING, SIZE + 2*PADDING);
}

void Host::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(widget);
        QPixmap pixmap(":/imgs/host.png");
        painter->drawPixmap(-SIZE/2, -SIZE/2, SIZE, SIZE, pixmap);
        if (option->state & QStyle::State_Selected) {
            painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
            painter->drawRect(boundingRect());
        }
        painter->setPen(Qt::black);
        QRectF textRect(-SIZE/2, SIZE/2 + 5, SIZE, 20);
        painter->drawText(textRect, Qt::AlignCenter, getName());
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

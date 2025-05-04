#include "controller.h"
#include "controllerdialog.h"
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>

Controller::Controller(QPoint position, int number, QGraphicsItem *parent)
    : NetNode(DeviceType::CONTROLLER, parent)
{
    setName(QString("c%0").arg(number));
    setIp("127.0.0.1");
    setPort("6653");

    setPos(position);
}

QRectF Controller::boundingRect() const
{
    return QRectF(-SIZE/2 - PADDING, -SIZE/2 - PADDING,
                 SIZE + 2*PADDING, SIZE + 2*PADDING);
}

void Controller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPixmap pixmap(":/imgs/controller.png");
    painter->drawPixmap(-SIZE/2, -SIZE/2, SIZE, SIZE, pixmap);
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
    painter->setPen(Qt::black);
    QRectF textRect(-SIZE/2, SIZE/2 + 5, SIZE, 20);
    painter->drawText(textRect, Qt::AlignCenter, getName());
}

void Controller::configure()
{
    ControllerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        update();
    }
}

QString Controller::getPort() const { return port; }
void Controller::setPort(const QString &port) { this->port = port; update(); }
QString Controller::getIp() const { return ip; }
void Controller::setIp(const QString &ip) { this->ip = ip; update(); }

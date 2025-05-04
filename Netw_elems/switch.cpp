#include "switch.h"
#include <QPainter>
#include <QPixmap>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QStyleOptionGraphicsItem>

Switch::Switch(QPoint position, int number, QGraphicsItem *parent)
    : NetNode(DeviceType::SWITCH, parent)
{
    setName(QString("s%0").arg(number));
    setPos(position);
}

QRectF Switch::boundingRect() const
{
    return QRectF(-SIZE/2 - PADDING, -SIZE/2 - PADDING,
                 SIZE + 2*PADDING, SIZE + 2*PADDING);
}

void Switch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QPixmap pixmap(":/imgs/switch.png");
    painter->drawPixmap(-SIZE/2, -SIZE/2, SIZE, SIZE, pixmap);
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
    painter->setPen(Qt::black);
    QRectF textRect(-SIZE/2, SIZE/2 + 5, SIZE, 20);
    painter->drawText(textRect, Qt::AlignCenter, getName());
}

void Switch::configure(){/*to do nothing*/}

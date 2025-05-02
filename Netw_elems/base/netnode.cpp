#include "netnode.h"

NetNode::NetNode(DeviceType type, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      deviceType(type),
      size(70, 70){
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF NetNode::boundingRect() const{
    return QRectF(0, 0, size.width(), size.height());
}

QVariant NetNode::itemChange(GraphicsItemChange change, const QVariant &value){
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

DeviceType NetNode::getDeviceType() const{return deviceType;}
QString NetNode::getName() const{return name;}
void NetNode::setName (const QString &name) {this->name=name; update();}

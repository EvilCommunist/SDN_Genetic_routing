#include "netnode.h"
#include "netlink.h"
#include <QDebug>

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
        updateLinks();
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void NetNode::updateLinks()
{
    for (NetLink* link : links) {
        link->updatePosition();
    }
}
void NetNode::addLink(NetLink* link) { links.append(link); }
void NetNode::removeLink(NetLink* link) { if (!scene()) return; else links.removeAll(link); }

DeviceType NetNode::getDeviceType() const{return deviceType;}
QString NetNode::getName() const{return name;}
void NetNode::setName (const QString &name) {this->name=name; update();}

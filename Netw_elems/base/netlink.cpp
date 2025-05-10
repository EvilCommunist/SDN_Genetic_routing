#include "netlink.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

NetLink::NetLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : QGraphicsItem(parent), node1(node1), node2(node2){
    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);
    updatePosition();
}

QRectF NetLink::boundingRect() const{
    return path.boundingRect().adjusted(-5, -5, 5, 5);
}

void NetLink::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*){
    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(path);

    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::blue, 2, Qt::DashLine));
        painter->drawPath(path);
    }
}

void NetLink::updatePosition(){
    prepareGeometryChange();
    updatePath();
    update();
}

QPointF NetLink::calculateCenter() const{
    return (node1->pos() + node2->pos()) / 2;
}

void NetLink::updatePath(){
    path = QPainterPath();
    path.moveTo(node1->pos());
    path.lineTo(node2->pos());
}

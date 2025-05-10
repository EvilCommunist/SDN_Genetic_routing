#include "ctoslink.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

CSLink::CSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : NetLink(node1, node2, parent){}

void CSLink::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPen oldPen = painter->pen();
    QPen newPen(Qt::black);
    newPen.setWidth(1);
    newPen.setStyle(Qt::DashLine);
    painter->setPen(newPen);
    painter->drawLine(line());
    painter->setPen(oldPen);
}

void CSLink::configure(){}

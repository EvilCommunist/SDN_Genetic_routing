#include "netlink.h"
#include <QPen>

NetLink::NetLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), node1(node1), node2(node2)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);
    setAcceptHoverEvents(true);

    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));

    if (node1){
        node1->addLink(this);
        node1Port = node1->getPort();
    }
    if (node2){
        node2->addLink(this);
        node2Port = node2->getPort();
    }

    updatePosition();
}
NetLink::~NetLink(){
    if (node1!=nullptr) node1->removeLink(this);
    if (node2!=nullptr) node2->removeLink(this);
}

void NetLink::updatePosition()
{
    prepareGeometryChange();
    updateLine();
}

void NetLink::updateLine()
{
    if (!node1 || !node2) return;

    prepareGeometryChange();
    QLineF newLine(node1->pos(), node2->pos());
    setLine(newLine);
}

QVariant NetLink::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged) {
        QPen p = pen();
        p.setColor(isSelected() ? Qt::blue : Qt::black);
        p.setStyle(isSelected() ? Qt::DashLine : Qt::SolidLine);
        setPen(p);
    }
    return QGraphicsLineItem::itemChange(change, value);
}

NetNode* NetLink::getNode1() const { return node1; }
NetNode* NetLink::getNode2() const { return node2; }

int NetLink::getPortNode1() const {return node1Port;}
int NetLink::getPortNode2() const {return node2Port;}
void NetLink::setPortNode1(int newValue) {node1Port=newValue;}
void NetLink::setPortNode2(int newValue) {node2Port=newValue;}

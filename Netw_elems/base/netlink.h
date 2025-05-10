#ifndef NETLINK_H
#define NETLINK_H

#include <QGraphicsItem>
#include "netnode.h"

class NetLink : public QGraphicsItem
{
public:
    NetLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent = nullptr);
    virtual ~NetLink() = default;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;

    NetNode* getNode1() const { return node1; }
    NetNode* getNode2() const { return node2; }

    virtual void updatePosition();
    virtual void configure() = 0;
    virtual DeviceType getDeviceType() const = 0;

protected:
    QPointF calculateCenter() const;
    void updatePath();

    NetNode* node1;
    NetNode* node2;
    QPainterPath path;
    static constexpr qreal ARROW_SIZE = 10.0;
};

#endif // NETLINK_H

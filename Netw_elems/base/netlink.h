#ifndef NETLINK_H
#define NETLINK_H

#include <QGraphicsLineItem>
#include "netnode.h"

class NetLink : public QGraphicsLineItem
{
public:
    NetLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent = nullptr);
    virtual ~NetLink();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    NetNode* getNode1() const;
    NetNode* getNode2() const;

    virtual void updatePosition();
    virtual void configure() = 0;
    virtual DeviceType getDeviceType() const = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateLine();

    NetNode* node1;
    NetNode* node2;
    static constexpr qreal ARROW_SIZE = 10.0;
};

#endif // NETLINK_H

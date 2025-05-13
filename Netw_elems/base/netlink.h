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

    int getPortNode1() const;
    int getPortNode2() const;
    void setPortNode1(int newValue);
    void setPortNode2(int newValue);

    virtual void updatePosition();
    virtual void configure() = 0;
    virtual DeviceType getDeviceType() const = 0;

    virtual float getBandwidth() const{}
    virtual void setBandwidth(float bw) {}
    virtual float getDelay() const {}
    virtual void setDelay(float delay) {}
    virtual float getPacketLoss() const {}
    virtual void setPacketLoss(float loss) {}

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void updateLine();

    NetNode* node1;
    NetNode* node2;
    int node1Port;
    int node2Port;
    static constexpr qreal ARROW_SIZE = 10.0;
};

#endif // NETLINK_H

#ifndef HSLINK_H
#define HSLINK_H

#include "base/netlink.h"
#include <QColor>

class HSLink : public NetLink
{
public:
    HSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    void configure() override;
    DeviceType getDeviceType() const override { return StoHLINK; }

    float getBandwidth() const;
    void setBandwidth(float bw);

    float getDelay() const;
    void setDelay(float delay);

    float getPacketLoss() const;
    void setPacketLoss(float loss);

    void setNormalState();
    void setSelectedState();
    void setMetricsState();

private:
    void updateToolTip();

    float bandwidth;
    float delay;
    float packetLoss;

    enum class State { Normal, Selected, Normal_Metrics };
    State state;
};

#endif // HSLINK_H

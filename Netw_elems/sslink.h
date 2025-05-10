#ifndef SSLINK_H
#define SSLINK_H

#include "base/netlink.h"
#include <QColor>

class SSLink : public NetLink
{
public:
    SSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    void configure() override;
    DeviceType getDeviceType() const override { return StoSLINK; }

    float getBandwidth() const;
    void setBandwidth(float bw);

    float getDelay() const;
    void setDelay(float delay);

    float getPacketLoss() const;
    void setPacketLoss(float loss);

    void setNormalState();
    void setSelectedState();
    void setIncludedInPathState(QColor color);
    void setIncludedInPathsState(QColor color);

private:
    void updateToolTip();

    float bandwidth;
    float delay;
    float packetLoss;

    enum class State { Normal, Selected, InPath, InPaths };
    State state;
    QColor pathColor;
};

#endif // SSLINK_H

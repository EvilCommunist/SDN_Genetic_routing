#ifndef CSLINK_H
#define CSLINK_H

#include "base/netlink.h"
#include <QColor>

class CSLink : public NetLink
{
public:
    CSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
               QWidget* widget = nullptr) override;
    void configure() override;
    DeviceType getDeviceType() const override { return CtoSLINK; }

private:
};

#endif // CSLINK_H

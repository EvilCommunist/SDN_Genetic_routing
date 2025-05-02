#ifndef NETNODE_H
#define NETNODE_H

#include <QGraphicsItem>
#include <QPainter>
#include "devices.h"

class NetNode : public QGraphicsItem
{
public:
    NetNode(DeviceType type, QGraphicsItem *parent = nullptr);
    virtual ~NetNode() = default;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override = 0;
    DeviceType getDeviceType() const;
    QString getName() const;
    void setName(const QString &name);
    virtual void configure() = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    DeviceType deviceType;
    QString name;
    QSizeF size;
};

#endif // NETNODE_H

#ifndef NETNODE_H
#define NETNODE_H

#include <QGraphicsItem>
#include <QPainter>
#include "devices.h"

class NetLink;

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
    void addLink(NetLink* link);
    void removeLink(NetLink* link);
    int getPort();
    void updateLinks();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    DeviceType deviceType;
    QString name;
    QSizeF size;
    QList<NetLink*> links;
};

#endif // NETNODE_H

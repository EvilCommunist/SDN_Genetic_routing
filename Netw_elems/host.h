#ifndef HOST_H
#define HOST_H

#include "base/netnode.h"
#include <QGraphicsItem>

class Host : public NetNode
{
public:
    explicit Host(QPoint position, int number = 0, QGraphicsItem *parent = nullptr);
    ~Host() override = default;
    Host(const Host&) = delete;
    Host& operator=(const Host&) = delete;
    QString getMacAddr() const;
    void setMacAddr(const QString &mac);
    QString getIpAddr() const;
    void setIpAddr(const QString &ip);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void configure() override;

private:
    QString macAddr;
    QString ipAddr;
};

#endif // HOST_H

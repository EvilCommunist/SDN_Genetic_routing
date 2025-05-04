#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "base/netnode.h"
#include <QGraphicsItem>

class Controller : public NetNode
{
public:
    explicit Controller(QPoint position, int number = 0, QGraphicsItem *parent = nullptr);
    ~Controller() override = default;
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    QString getPort() const;
    void setPort(const QString &port);
    QString getIp() const;
    void setIp(const QString &ip);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void configure() override;

private:
    QString ip;
    QString port;
    static constexpr qreal SIZE = 64.0;
    static constexpr qreal PADDING = 3.0;
};

#endif

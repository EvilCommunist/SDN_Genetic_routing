#ifndef SWITCH_H
#define SWITCH_H

#include "base/netnode.h"
#include <QGraphicsItem>

class Switch : public NetNode
{
public:
    explicit Switch(QPoint position, int number = 0, QGraphicsItem *parent = nullptr);
    ~Switch() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    void configure() override;

private:
    static constexpr qreal SIZE = 64.0;
    static constexpr qreal PADDING = 3.0;
};

#endif // SWITCH_H

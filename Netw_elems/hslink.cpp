#include "hslink.h"
#include "linkparamdialog.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

HSLink::HSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : NetLink(node1, node2, parent),
      bandwidth(1.0),
      delay(1.0),
      packetLoss(0.01),
      state(State::Normal){
    updateToolTip();
    setNormalState();
}

void HSLink::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    NetLink::paint(painter, option, widget);

    if (option->state & QStyle::State_Selected) {
        QString metrics = QString("BW: %1 Mbps\nDelay: %2 ms\nLoss: %3%")
                         .arg(bandwidth).arg(delay).arg(packetLoss*100);

        QFontMetrics fm(painter->font());
        QRect textRect = fm.boundingRect(QRect(), Qt::AlignCenter, metrics);
        QPointF center = (line().p1() + line().p2()) / 2;
        textRect.moveCenter(center.toPoint());

        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);
        painter->drawRect(textRect.adjusted(-5, -5, 5, 5));
        painter->drawText(textRect, Qt::AlignCenter, metrics);
    }else if (option->state & QStyle::State_MouseOver) {
        QString metrics = QString("BW: %1 Mbps\nDelay: %2 ms\nLoss: %3%")
                         .arg(bandwidth).arg(delay).arg(packetLoss*100);
        QFontMetrics fm(painter->font());
        QRect textRect = fm.boundingRect(QRect(), Qt::AlignCenter, metrics);
        QPointF center = (line().p1() + line().p2()) / 2;
        textRect.moveCenter(center.toPoint());

        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);
        painter->drawRect(textRect.adjusted(-5, -5, 5, 5));
        painter->drawText(textRect, Qt::AlignCenter, metrics);
    }
}

void HSLink::configure(){
    linkParamDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        updateToolTip();
        update();
    }
}

void HSLink::setNormalState(){
    state = State::Normal;
    update();
}

void HSLink::setSelectedState(){
    state = State::Selected;
    update();
}

void HSLink::updateToolTip(){
    setToolTip(QString("SSLink\nBandwidth: %1 Mbps\nDelay: %2 ms\nPacket Loss: %3%")
              .arg(bandwidth).arg(delay).arg(packetLoss*100));
}

float HSLink::getBandwidth() const { return bandwidth; }
void HSLink::setBandwidth(float bw) { bandwidth = bw; update(); }

float HSLink::getDelay() const { return delay; }
void HSLink::setDelay(float delay) { delay = delay; update(); }

float HSLink::getPacketLoss() const { return packetLoss; }
void HSLink::setPacketLoss(float loss) { packetLoss = loss; update(); }

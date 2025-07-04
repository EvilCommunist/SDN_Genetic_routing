#include "sslink.h"
#include "linkparamdialog.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

SSLink::SSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : NetLink(node1, node2, parent),
      bandwidth(1.0),
      delay(1.0),
      packetLoss(0.01),
      state(State::Normal){
    updateToolTip();
    setNormalState();
}

void SSLink::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPen pen;
    switch(state) {
        case State::InPath:
            pen.setColor(pathColor);
            pen.setWidth(4);
            break;
        case State::Selected:
            pen.setColor(Qt::blue);
            pen.setWidth(2);
            break;
        case State::Normal:
        case State::Normal_Metrics:
        default:
            pen.setColor(Qt::black);
            pen.setWidth(2);
            break;
    }
    painter->setPen(pen);
    painter->drawLine(line());

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
    } else if (option->state & QStyle::State_MouseOver) {
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
    } else if(state == State::Normal_Metrics){
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

void SSLink::configure(){
    linkParamDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        updateToolTip();
        update();
    }
}

void SSLink::setNormalState(){
    state = State::Normal;
    update();
}

void SSLink::setSelectedState(){
    state = State::Selected;
    update();
}

void SSLink::setIncludedInPathState(QColor color){
    state = State::InPath;
    pathColor = color;
    update();
}

void SSLink::setIncludedInPathsState(QColor color){
    state = State::InPaths;
    pathColor = color;
    update();
}

void SSLink::setMetricsState(){
    state = State::Normal_Metrics;
    update();
}

void SSLink::updateToolTip(){
    setToolTip(QString("SSLink\nBandwidth: %1 Mbps\nDelay: %2 ms\nPacket Loss: %3%")
              .arg(bandwidth).arg(delay).arg(packetLoss*100));
}

float SSLink::getBandwidth() const { return bandwidth; }
void SSLink::setBandwidth(float bw) { bandwidth = bw; update(); }

float SSLink::getDelay() const { return delay; }
void SSLink::setDelay(float delay) { this->delay = delay; update(); }

float SSLink::getPacketLoss() const { return packetLoss; }
void SSLink::setPacketLoss(float loss) { packetLoss = loss; update(); }

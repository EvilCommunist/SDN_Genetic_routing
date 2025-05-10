#include "sslink.h"
#include "linkparamdialog.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

SSLink::SSLink(NetNode* node1, NetNode* node2, QGraphicsItem* parent)
    : NetLink(node1, node2, parent),
      bandwidth(1.0),
      delay(1.0),
      packetLoss(0.0),
      state(State::Normal){
    updateToolTip();
    setNormalState();
}

void SSLink::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    QPen pen;

    switch(state) {
    case State::Selected:
        pen = QPen(Qt::blue, 4);
        break;
    case State::InPath:
    case State::InPaths:
        pen = QPen(pathColor, 4, Qt::DashLine);
        break;
    default:
        pen = QPen(Qt::black, 3);
    }

    painter->setPen(pen);
    painter->drawPath(path);

    if (option->state & QStyle::State_Selected) {
        QString metrics = QString("BW: %1 Mbps\nDelay: %2 ms\nLoss: %3%")
                         .arg(bandwidth).arg(delay).arg(packetLoss*100);

        QFontMetrics fm(painter->font());
        QRect textRect = fm.boundingRect(QRect(), Qt::AlignCenter, metrics);
        textRect.moveCenter(calculateCenter().toPoint());

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

void SSLink::updateToolTip(){
    setToolTip(QString("SSLink\nBandwidth: %1 Mbps\nDelay: %2 ms\nPacket Loss: %3%")
              .arg(bandwidth).arg(delay).arg(packetLoss*100));
}

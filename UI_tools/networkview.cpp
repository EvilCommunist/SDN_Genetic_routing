#include "networkview.h"
#include <QMouseEvent>

NetworkView::NetworkView(QWidget *parent)
    : QGraphicsView(parent),
      currentMode(DeviceType::EDIT)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setSceneRect(-1000, -1000, 2000, 2000);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void NetworkView::setHostMode()
{
    currentMode = DeviceType::HOST;
    setDragMode(QGraphicsView::NoDrag);
    setCursor(Qt::PointingHandCursor);
}

void NetworkView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && currentMode == DeviceType::HOST) {
        QPointF scenePos = mapToScene(event->pos());
        createHost(scenePos);
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void NetworkView::createHost(const QPointF &pos)
{
    Host *host = new Host(pos.toPoint(), ++hostCounter);

    host->setFlag(QGraphicsItem::ItemIsMovable);
    host->setFlag(QGraphicsItem::ItemIsSelectable);
    host->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    scene->addItem(host);
    scene->update();
}

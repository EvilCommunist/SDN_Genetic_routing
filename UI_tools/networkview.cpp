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
void NetworkView::setControllerMode()
{
    currentMode = DeviceType::CONTROLLER;
    setDragMode(QGraphicsView::NoDrag);
    setCursor(Qt::PointingHandCursor);
}
void NetworkView::setSwitchMode()
{
    currentMode = DeviceType::SWITCH;
    setDragMode(QGraphicsView::NoDrag);
    setCursor(Qt::PointingHandCursor);
}
void NetworkView::setEditMode()
{
    currentMode = DeviceType::EDIT;
    setDragMode(QGraphicsView::RubberBandDrag);
    setCursor(Qt::ArrowCursor);
}

void NetworkView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());

        switch(currentMode) {
        case DeviceType::HOST:
            createHost(scenePos);
            return;
        case DeviceType::CONTROLLER:
            createController(scenePos);
            return;
        case DeviceType::SWITCH:
            createSwitch(scenePos);
            return;
        default:
            break;
        }
    }
    QGraphicsView::mousePressEvent(event);
}
void NetworkView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (currentMode == DeviceType::EDIT && event->button() == Qt::LeftButton) {
        editSelectedItem();
        return;
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void NetworkView::setupNetworkElement(QGraphicsItem *item)
{
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    scene->update();
}

void NetworkView::createHost(const QPointF &pos)
{
    Host *host = new Host(pos.toPoint(), ++hostCounter);
    setupNetworkElement(host);
    scene->addItem(host);
}
void NetworkView::createController(const QPointF &pos)
{
    Controller *controller = new Controller(pos.toPoint(), ++controllerCounter);
    setupNetworkElement(controller);
    scene->addItem(controller);
}
void NetworkView::createSwitch(const QPointF &pos)
{
    Switch *sw = new Switch(pos.toPoint(), ++switchCounter);
    setupNetworkElement(sw);
    scene->addItem(sw);
}

void NetworkView::editSelectedItem()
{
    QGraphicsItem* selectedItem = scene->selectedItems().value(0);

    if (!selectedItem) return;

    if (auto host = dynamic_cast<Host*>(selectedItem)) {
        host->configure();
    }
    else if (auto controller = dynamic_cast<Controller*>(selectedItem)) {
        controller->configure();
    }
    else if (auto switchItem = dynamic_cast<Switch*>(selectedItem)) {
        switchItem->configure();
    }
}


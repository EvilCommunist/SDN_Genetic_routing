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
void NetworkView::setLinkMode()
{
    currentMode = DeviceType::LINK;
    setDragMode(QGraphicsView::NoDrag);
    setCursor(Qt::CrossCursor);
    firstLinkNode = nullptr;
}
void NetworkView::setEditMode()
{
    currentMode = DeviceType::EDIT;
    setDragMode(QGraphicsView::RubberBandDrag);
    setCursor(Qt::ArrowCursor);
}

void NetworkView::renumberHosts() {
    int counter = 0, curItems = 0;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* host = dynamic_cast<Host*>(item)) {
            counter++;
        }
    }
    curItems = counter;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* host = dynamic_cast<Host*>(item)) {
            host->setName("h" + QString::number(counter--));
        }
    }
    hostCounter = curItems;
}

void NetworkView::renumberControllers() {
    int counter = 0, curItems = 0;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* controller = dynamic_cast<Controller*>(item)) {
            counter++;
        }
    }
    curItems = counter;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* controller = dynamic_cast<Controller*>(item)) {
            controller->setName("c" + QString::number(counter--));
        }
    }
    controllerCounter = curItems;
}

void NetworkView::renumberSwitches() {
    int counter = 0, curItems = 0;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* sw = dynamic_cast<Switch*>(item)) {
            counter++;
        }
    }
    curItems = counter;
    for (QGraphicsItem* item : scene->items()) {
        if (auto* sw = dynamic_cast<Switch*>(item)) {
            sw->setName("s" + QString::number(counter--));
        }
    }
    switchCounter = curItems;
}

void NetworkView::renumberAllNodes() {
    renumberHosts();
    renumberControllers();
    renumberSwitches();
}

void NetworkView::deleteSelectedItems()
{
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();

    QList<QGraphicsItem*> allItems = scene->items();
    for (QGraphicsItem* item : allItems) {
        if (auto link = dynamic_cast<NetLink*>(item)) {
            NetNode* from = link->getNode1();
            NetNode* to = link->getNode2();

            if (selectedItems.contains(from) || selectedItems.contains(to)) {
                scene->removeItem(link);
                delete link;
            }
        }
    }

    for (QGraphicsItem* item : selectedItems) {
        scene->removeItem(item);
        delete item;
    }

    renumberAllNodes();

    scene->update();
}

void NetworkView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        QGraphicsItem *item = scene->itemAt(scenePos, QTransform());

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
        case DeviceType::LINK:
            if (item) {
                if (auto node = dynamic_cast<NetNode*>(item)) {
                    if (!firstLinkNode) {
                        if (node->getDeviceType() == DeviceType::SWITCH ||
                            node->getDeviceType() == DeviceType::HOST ||
                            node->getDeviceType() == DeviceType::CONTROLLER) {
                            firstLinkNode = node;
                            node->setSelected(true);
                        }
                    } else if (firstLinkNode != node) {
                        bool connectable = (firstLinkNode->getDeviceType() == DeviceType::SWITCH && node->getDeviceType() == DeviceType::SWITCH) ||
                                           (firstLinkNode->getDeviceType() == DeviceType::HOST && node->getDeviceType() == DeviceType::SWITCH) ||
                                           (firstLinkNode->getDeviceType() == DeviceType::SWITCH && node->getDeviceType() == DeviceType::HOST)||
                                           (firstLinkNode->getDeviceType() == DeviceType::CONTROLLER && node->getDeviceType() == DeviceType::SWITCH)||
                                           (firstLinkNode->getDeviceType() == DeviceType::SWITCH && node->getDeviceType() == DeviceType::CONTROLLER);
                        if (connectable) {
                            createLink(firstLinkNode, node);
                        }
                        resetLinkMode();
                    }
                }
            }
            return;
        default:
            break;
        }
    }
    QGraphicsView::mousePressEvent(event);
}
void NetworkView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && (currentMode == DeviceType::StoSLINK || currentMode == DeviceType::StoHLINK || currentMode == DeviceType::LINK)) {
        resetLinkMode();
    }
    QGraphicsView::mouseReleaseEvent(event);
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
void NetworkView::createLink(NetNode *from, NetNode *to)
{
    NetLink *link = nullptr;

    if (from->getDeviceType() == DeviceType::SWITCH &&
        to->getDeviceType() == DeviceType::SWITCH) {
        link = new SSLink(from, to);
    }
    else if ((from->getDeviceType() == DeviceType::HOST &&
              to->getDeviceType() == DeviceType::SWITCH) ||
             (from->getDeviceType() == DeviceType::SWITCH &&
              to->getDeviceType() == DeviceType::HOST)) {
        link = new HSLink(from, to);
    }
    else if ((from->getDeviceType() == DeviceType::CONTROLLER &&
              to->getDeviceType() == DeviceType::SWITCH) ||
             (from->getDeviceType() == DeviceType::SWITCH &&
              to->getDeviceType() == DeviceType::CONTROLLER)) {
        link = new CSLink(from, to);
    }

    if (link) {
        scene->addItem(link);
        from->addLink(link);
        to->addLink(link);
    }
}
void NetworkView::resetLinkMode()
{
    if (firstLinkNode) {
        firstLinkNode->setSelected(false);
        firstLinkNode = nullptr;
    }
    setCursor(Qt::CrossCursor);
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
    else if (auto link = dynamic_cast<SSLink*>(selectedItem)) {
        link->configure();
    }
    else if (auto link = dynamic_cast<HSLink*>(selectedItem)) {
        link->configure();
    }
}


QGraphicsScene* NetworkView::getScene() const{return this->scene;}

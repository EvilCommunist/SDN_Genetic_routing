#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Netw_elems/base/devices.h"
#include "Netw_elems/host.h"
#include "Netw_elems/controller.h"
#include "Netw_elems/switch.h"
#include "Netw_elems/sslink.h"

class NetworkView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit NetworkView(QWidget *parent = nullptr);
    ~NetworkView() = default;

public slots:
    void setControllerMode();
    void setHostMode();
    void setSwitchMode();
    void setLinkMode();
    void setEditMode();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    DeviceType currentMode;
    int hostCounter = 0;
    int controllerCounter = 0;
    int switchCounter = 0;
    NetNode *firstLinkNode = nullptr;

    void createHost(const QPointF &pos);
    void createController(const QPointF &pos);
    void createSwitch(const QPointF &pos);
    void createLink(NetNode *from, NetNode *to);
    void setupNetworkElement(QGraphicsItem *item);
    void editSelectedItem();
    void resetLinkMode();
};

#endif // NETWORKVIEW_H

#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Netw_elems/base/devices.h"
#include "Netw_elems/host.h"
#include "Netw_elems/controller.h"
#include "Netw_elems/switch.h"
#include "Netw_elems/sslink.h"
#include "Netw_elems/hslink.h"
#include "Netw_elems/ctoslink.h"

class NetworkView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit NetworkView(QWidget *parent = nullptr);
    ~NetworkView() = default;
    QGraphicsScene* getScene() const;
    void prepScene();
    NetNode* loadNode(const QPointF &pos, DeviceType type);
    NetLink* loadLink(NetNode* n1, NetNode* n2);

public slots:
    void setControllerMode();
    void setHostMode();
    void setSwitchMode();
    void setLinkMode();
    void setEditMode();
    void deleteSelectedItems();

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

    void clear();

    Host* createHost(const QPointF &pos);
    Controller* createController(const QPointF &pos);
    Switch* createSwitch(const QPointF &pos);
    NetLink* createLink(NetNode *from, NetNode *to);
    void setupNetworkElement(QGraphicsItem *item);
    void editSelectedItem();
    void resetLinkMode();

    void renumberHosts();
    void renumberControllers();
    void renumberSwitches();
    void renumberAllNodes();
};

#endif // NETWORKVIEW_H

#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Netw_elems/base/devices.h"
#include "Netw_elems/host.h"

class NetworkView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit NetworkView(QWidget *parent = nullptr);
    ~NetworkView() = default;

public slots:
    void setHostMode();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    DeviceType currentMode;
    int hostCounter = 0;

    void createHost(const QPointF &pos);
};

#endif // NETWORKVIEW_H

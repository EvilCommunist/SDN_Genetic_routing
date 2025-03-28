#ifndef ANYDEVICE_H
#define ANYDEVICE_H

#include <QPainter>
#include "devices.h"

class anyDevice
{
private:
    int id;
public:
    anyDevice();
    virtual ~anyDevice();
    virtual QSize getSize() const = 0;
    virtual QPoint getPos() const = 0;
    virtual void setPos(QPoint pos) = 0;
    //virtual void configure() = 0;
    virtual void select() = 0;
    virtual void removeSelection() = 0;
    virtual QString getName() = 0;
    virtual void setName(QString name) = 0;
    virtual DeviceType getDeviceType() = 0;
    inline void setId(int id);
    inline int getId() const;
};

#endif // ANYDEVICE_H

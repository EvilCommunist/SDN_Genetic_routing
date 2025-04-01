#ifndef NETNODE_H
#define NETNODE_H

#include "anydevice.h"
#include "devices.h"

class NetNode: public anyDevice
{
private:
    QString name;
    QPoint pos;
protected:
    bool isSelected;
public:
    NetNode();
    virtual QPoint getPos() const;
    virtual void setPos(QPoint pos);
    virtual void configure()=0;
    virtual void select();
    virtual void removeSelection();
    virtual QString getName();
    virtual void setName(QString name);
};

#endif // NETNODE_H

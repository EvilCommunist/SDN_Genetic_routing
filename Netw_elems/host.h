#ifndef HOST_H
#define HOST_H

#include"base/netnode.h"

class Host : public NetNode
{
private:
    QString macAddr;
    QString ipAddr;
public:
    Host(QPoint position);
    ~Host();
    inline QString getMacAddr() const;
    inline void setMacAddr(QString mac);
    inline QString getIpAddr() const;
    inline void setIpAddr(QString ip);

    virtual void configure();
    void create(int num);

    virtual void draw(/*NetworkMapDrawer *drawer*/);
    virtual DeviceType getDeviceType();
    virtual QSize getSize() const;
};

#endif // HOST_H

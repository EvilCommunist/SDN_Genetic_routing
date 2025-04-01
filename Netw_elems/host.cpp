#include "host.h"
#include"hostdialog.h"

Host::Host(QPoint pos){
    removeSelection();
    setPos(pos);
}
Host::~Host(){}

void Host::setIpAddr(QString ip){this->ipAddr=ip;}
QString Host::getIpAddr()const{return this->ipAddr;}

void Host::setMacAddr(QString mac){this->macAddr=mac;}
QString Host::getMacAddr()const{return this->macAddr;}

DeviceType Host::getDeviceType(){return HOST;}

void Host::configure(){
    HostDialog dialog(this);
    dialog.exec();
}

void Host::create(int num){
    setName(QString("h%0").arg(num));
    setIpAddr(QString("10.0.0.%0").arg(num));
    setMacAddr(QString("00:00:00:00:00:%0").arg(num, 2, 10, QChar('0')));
}

// TODO:
void Host::draw(/*NetworkMapDrawer *drawer*/){/*do drawings*/}
QSize Host::getSize()const{return QSize();/*do somethings*/}

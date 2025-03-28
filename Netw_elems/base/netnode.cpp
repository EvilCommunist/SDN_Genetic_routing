#include "netnode.h"

NetNode::NetNode(){}

void NetNode::setPos(QPoint pos){this->pos = pos;}
QPoint NetNode::getPos() const{return this->pos;}

void NetNode::select(){this->isSelected=true;}
void NetNode::removeSelection(){this->isSelected=false;}

void NetNode::setName(QString name){this->name = name;}
QString NetNode::getName(){return this->name;}

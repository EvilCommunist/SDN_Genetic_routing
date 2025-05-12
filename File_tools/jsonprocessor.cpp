#include "jsonprocessor.h"
#include <QFile>

bool JSONProcessor::saveJSONFile(const NetworkView* topology, const QString& filename){
    QJsonObject root;
    QJsonArray nodes;
    QJsonArray links;

    for (QGraphicsItem* item : topology->getScene()->items()) {
        if (auto node = dynamic_cast<NetNode*>(item)) {
            QJsonObject nodeObj;
            nodeObj["type"] = static_cast<int>(node->getDeviceType());
            nodeObj["name"] = node->getName();
            nodeObj["x"] = node->pos().x();
            nodeObj["y"] = node->pos().y();

            if(auto controller = dynamic_cast<Controller*>(node)){
                nodeObj["ip"] = controller->getIp();
                nodeObj["port"] = controller->getPort();
            }

            if (auto host = dynamic_cast<Host*>(node)) {
                nodeObj["ip"] = host->getIpAddr();
                nodeObj["mac"] = host->getMacAddr();
            }

            nodes.append(nodeObj);
        }
    }

    for (QGraphicsItem* item : topology->getScene()->items()) {
        if (auto link = dynamic_cast<NetLink*>(item)) {
            QJsonObject linkObj;
            linkObj["from"] = link->getNode1()->getName();
            linkObj["to"] = link->getNode2()->getName();

            if (auto paramLink = dynamic_cast<SSLink*>(link)) {
                linkObj["bandwidth"] = paramLink->getBandwidth();
                linkObj["delay"] = paramLink->getDelay();
                linkObj["loss"] = paramLink->getPacketLoss();
            }

            if (auto paramLink = dynamic_cast<HSLink*>(link)) {
                linkObj["bandwidth"] = paramLink->getBandwidth();
                linkObj["delay"] = paramLink->getDelay();
                linkObj["loss"] = paramLink->getPacketLoss();
            }

            links.append(linkObj);
        }
    }

    root["nodes"] = nodes;
    root["links"] = links;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    file.write(QJsonDocument(root).toJson());
    return true;
}

bool JSONProcessor::loadJSONFile(NetworkView *topology, const QString &filename){

}

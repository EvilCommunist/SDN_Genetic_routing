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
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    topology->prepScene();
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    QMap<QString, NetNode*> nodeMap;

    for (const QJsonValue& nodeVal : root["nodes"].toArray()) {
        QJsonObject nodeObj = nodeVal.toObject();
        DeviceType type = static_cast<DeviceType>(nodeObj["type"].toInt());
        QPointF pos(nodeObj["x"].toDouble(), nodeObj["y"].toDouble());

        NetNode* node = nullptr;
        switch (type) {
            case HOST:
                node = topology->loadNode(pos, DeviceType::HOST);
                dynamic_cast<Host*>(node)->setIpAddr(nodeObj["ip"].toString());
                dynamic_cast<Host*>(node)->setMacAddr(nodeObj["mac"].toString());
                break;
            case SWITCH:
                node = topology->loadNode(pos, DeviceType::SWITCH);
                break;
            case CONTROLLER:
                node = topology->loadNode(pos, DeviceType::CONTROLLER);
                dynamic_cast<Controller*>(node)->setIp(nodeObj["ip"].toString());
                dynamic_cast<Controller*>(node)->setPort(nodeObj["port"].toString());
                break;
        }

        if (node) {
            node->setName(nodeObj["name"].toString());
            nodeMap[node->getName()] = node;
        }
    }

    for (const QJsonValue& linkVal : root["links"].toArray()) {
        QJsonObject linkObj = linkVal.toObject();
        NetNode* from = nodeMap[linkObj["from"].toString()];
        NetNode* to = nodeMap[linkObj["to"].toString()];

        if (from && to) {
            NetLink* link = topology->loadLink(from, to);
            if (auto paramLink = dynamic_cast<NetLink*>(link)) {
                paramLink->setBandwidth(linkObj["bandwidth"].toDouble());
                paramLink->setDelay(linkObj["delay"].toDouble());
                paramLink->setPacketLoss(linkObj["loss"].toDouble());
            }
        }
    }

    return true;
}

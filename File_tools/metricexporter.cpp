#include "metricexporter.h"
#include <QStringBuilder>
#include <QTextStream>
#include "../Netw_elems/switch.h"

bool metricExporter::saveMetric(const QString& metrics, const QString& filename){
    QFile metricsFile(filename);

    if(!metricsFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream ostream(&metricsFile);
    ostream << metrics;

    metricsFile.close();
    return (ostream.status() == QTextStream::Ok);
}

QString metricExporter::exportMetrics(const QList<NetNode*>& nodes, const QList<NetLink*>& links)
{
    QString result;

    auto delayMatrix = generateAdjacencyMatrix(nodes, links, DELAY);
    result += "Delay Matrix (ms):\n";
    for (const auto& row : delayMatrix) {
        for (float val : row) {
            result += QString::number(val) + " ";
        }
        result += "\n";
    }
    result += "\n";

    auto bandwidthMatrix = generateAdjacencyMatrix(nodes, links, BANDWIDTH);
    result += "Bandwidth Matrix (Mbps):\n";
    for (const auto& row : bandwidthMatrix) {
        for (float val : row) {
            result += QString::number(val) + " ";
        }
        result += "\n";
    }
    result += "\n";

    auto lossMatrix = generateAdjacencyMatrix(nodes, links, PACKET_LOSS);
    result += "Packet Loss Matrix (%):\n";
    for (const auto& row : lossMatrix) {
        for (float val : row) {
            result += QString::number(val) + " ";
        }
        result += "\n";
    }
    result += "\n";

    result += "Switch-Host Metrics:\n";
    result += generateSwitchHostMetrics(nodes, links);

    return result;
}

QVector<QVector<float>> metricExporter::generateAdjacencyMatrix(const QList<NetNode*>& nodes,
                                                                const QList<NetLink*>& links,
                                                                MetricType metricType)
{
    QList<Switch*> switches{};
    for(auto node:nodes){
        if(auto sw = dynamic_cast<Switch*>(node))
            switches.append(sw);
    }

    int size = switches.size();
    QVector<QVector<float>> matrix(size, QVector<float>(size, 0.0f));

    QMap<NetNode*, int> switchIndex;
    for (int i = 0; i < size; ++i) {
        switchIndex[switches[i]] = i;
    }

    for (NetLink* link : links) {
        if(!dynamic_cast<Switch*>(link->getNode1()) || !dynamic_cast<Switch*>(link->getNode2()))
            continue;
        int i = switchIndex[link->getNode1()];
        int j = switchIndex[link->getNode2()];
        float metric = getLinkMetric(link, metricType);
        if (i == j)
            continue;
        matrix[i][j] = metric;
        matrix[j][i] = metric;
    }

    auto matrix_reversed = matrix;
    for(auto i=0; i<matrix_reversed.size(); i++){
        for(auto j=0; j<matrix_reversed.size(); j++){
            matrix_reversed[i][j] = matrix[matrix.size()-1-i][matrix.size()-1-j];
        }
    }

    return matrix_reversed;
}

QString metricExporter::generateSwitchHostMetrics(const QList<NetNode*>& nodes, const QList<NetLink*>& links)
{
    QString result;

    for (NetLink* link : links) {
        NetNode* node1 = link->getNode1();
        NetNode* node2 = link->getNode2();
        bool isSwitchHost = (node1->getDeviceType() == SWITCH && node2->getDeviceType() == HOST) ||
                           (node1->getDeviceType() == HOST && node2->getDeviceType() == SWITCH);

        if (isSwitchHost) {
            QString node1Name = node1->getName();
            QString node2Name = node2->getName();

            result += QString("%1-%2: %3, %4, %5\n").arg(node1Name)
                                                    .arg(node2Name)
                                                    .arg(getLinkMetric(link, DELAY))
                                                    .arg(getLinkMetric(link, BANDWIDTH))
                                                    .arg(getLinkMetric(link, PACKET_LOSS));
        }
    }

    return result;
}

float metricExporter::getLinkMetric(NetLink* link, MetricType metricType)
{
    switch (metricType) {
    case DELAY:
        return link->getDelay();
    case BANDWIDTH:
        return link->getBandwidth();
    case PACKET_LOSS:
        return link->getPacketLoss()*100;
    default:
        return 0.0f;
    }
}

#ifndef METRICEXPORTER_H
#define METRICEXPORTER_H

#include <QString>
#include <QMap>
#include <QList>
#include "../Netw_elems/base/netnode.h"
#include "../Netw_elems/base/netlink.h"

class metricExporter
{
public:
    enum MetricType {
        DELAY,
        BANDWIDTH,
        PACKET_LOSS
    };
    static QString exportMetrics(const QList<NetNode*>& nodes, const QList<NetLink*>& links);
    static bool saveMetric(const QString& metrics, const QString& filename);

private:
    static QVector<QVector<float>> generateAdjacencyMatrix(const QList<NetNode*>& nodes,
                                                           const QList<NetLink*>& links,
                                                           MetricType metricType);

    static QString generateSwitchHostMetrics(const QList<NetNode*>& nodes, const QList<NetLink*>& links);

    static float getLinkMetric(NetLink* link, MetricType metricType);
};

#endif // METRICEXPORTER_H

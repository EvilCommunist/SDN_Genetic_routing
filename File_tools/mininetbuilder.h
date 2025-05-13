#ifndef MININETBUILDER_H
#define MININETBUILDER_H

#include <QString>
#include <QList>
#include <QFile>
#include "../Netw_elems/base/netnode.h"
#include "../Netw_elems/base/netlink.h"

class mininetBuilder
{
public:
    static QString generateMininetScript(const QList<NetNode*>& nodes,
                                         const QList<NetLink*>& links,
                                         const QString& controllerIp = "127.0.0.1", // default values
                                         int controllerPort = 6653);
    static bool saveMNScript(const QString& script, const QString& filename);
private:
    static QString generatePrefix();
    static QString generateControllers(const QString& ip, int port);
    static QString generateSwitches(const QList<NetNode*>& nodes);
    static QString generateHosts(const QList<NetNode*>& nodes);
    static QString generateLinks(const QList<NetLink*>& links);
    static QString generateAppendix();

    static QString nodeToMininetName(NetNode* node);
};

#endif // MININETBUILDER_H

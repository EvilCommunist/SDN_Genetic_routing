#include "mininetbuilder.h"
#include <QStringBuilder>
#include <QTextStream>
#include "../Netw_elems/sslink.h"
#include "../Netw_elems/hslink.h"
#include "../Netw_elems/switch.h"
#include "../Netw_elems/host.h"


bool mininetBuilder::saveMNScript(const QString& script, const QString& filename){
    QFile scriptFile(filename);

    if(!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream ostream(&scriptFile);
    ostream << script;

    scriptFile.close();
    return (ostream.status() == QTextStream::Ok);
}

QString mininetBuilder::generateMininetScript(const QList<NetNode*>& nodes,
                                            const QList<NetLink*>& links,
                                            const QString& controllerIp,
                                            int controllerPort)
{
    QString script;
    script += generatePrefix();
    script += generateControllers(controllerIp, controllerPort);
    script += generateHosts(nodes);
    script += generateSwitches(nodes);
    script += generateLinks(links);
    script += generateAppendix();
    return script;
}

QString mininetBuilder::generatePrefix()
{
    return R"(
from mininet.net import Mininet
from mininet.node import Controller, RemoteController, OVSKernelSwitch
from mininet.cli import CLI
from mininet.log import setLogLevel
from mininet.link import TCLink

def topology():
    net = Mininet(controller=RemoteController, link=TCLink, switch=OVSKernelSwitch)

)";
}

QString mininetBuilder::generateControllers(const QString& ip, int port)
{
    return QString("    c0 = net.addController('c0', controller=RemoteController, ip='%1', port=%2)\n\n")
           .arg(ip).arg(port);
}

QString mininetBuilder::generateSwitches(const QList<NetNode*>& nodes)
{
    QString switches;
    for (NetNode* node : nodes) {
        if(auto sw = dynamic_cast<Switch*>(node))
            switches += QString("    %1 = net.addSwitch('%1')\n").arg(nodeToMininetName(node));
    }
    return switches + "\n";
}

QString mininetBuilder::generateHosts(const QList<NetNode*>& nodes)
{
    QString hosts;
    for (NetNode* node : nodes) {
        if(auto host = dynamic_cast<Host*>(node))
            hosts += QString("    %1 = net.addHost('%1', mac='%2', ip='%3')\n")
                                               .arg(nodeToMininetName(node))
                                               .arg(host->getMacAddr())
                                               .arg(host->getIpAddr());
    }
    return hosts + "\n";
}

QString mininetBuilder::generateLinks(const QList<NetLink*>& links)
{
    QString linkStr;
    for (NetLink* link : links) {
        if (auto stosLink = dynamic_cast<SSLink*>(link)) {
            linkStr += QString("    net.addLink(%1, %2, port1=%3, port2=%4, bw=%5, delay='%6ms', loss=%7)\n")
                .arg(nodeToMininetName(link->getNode1()))
                .arg(nodeToMininetName(link->getNode2()))
                .arg(link->getPortNode1())
                .arg(link->getPortNode2())
                .arg(stosLink->getBandwidth())
                .arg(stosLink->getDelay())
                .arg(stosLink->getPacketLoss()*100);
        } else if (auto stosLink = dynamic_cast<HSLink*>(link)) {
            linkStr += QString("    net.addLink(%1, %2, port1=%3, port2=%4, bw=%5, delay='%6ms', loss=%7)\n")
                .arg(nodeToMininetName(link->getNode1()))
                .arg(nodeToMininetName(link->getNode2()))
                .arg(link->getPortNode1())
                .arg(link->getPortNode2())
                .arg(stosLink->getBandwidth())
                .arg(stosLink->getDelay())
                .arg(stosLink->getPacketLoss()*100);
        } else {
            linkStr += QString("    net.addLink(%1, %2)\n")
                .arg(nodeToMininetName(link->getNode1()))
                .arg(nodeToMininetName(link->getNode2()));
        }
    }
    return linkStr + "\n";
}

QString mininetBuilder::generateAppendix()
{
    return R"(
    c0.start()
    for sw in net.switches:
        sw.start([c0])

    net.build()
    CLI(net)
    net.stop()

if __name__ == '__main__':
    setLogLevel('info')
    topology()
)";
}

QString mininetBuilder::nodeToMininetName(NetNode* node)
{
    QString name = node->getName().toLower().replace(" ", "");
    return name.replace(QRegExp("[^a-z0-9]"), "");
}

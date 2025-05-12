#ifndef JSONPROCESSOR_H
#define JSONPROCESSOR_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "../UI_tools/networkview.h" // already contains all elements of network

class JSONProcessor
{
public:
    static bool saveJSONFile(const NetworkView* topology, const QString& filename);
    static bool loadJSONFile(NetworkView* topology, const QString& filename);
};

#endif // JSONPROCESSOR_H

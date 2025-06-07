#include "pathgetter.h"

QVector<int> PathGetter::get(QString path)
{
    QVector<int> decodedPath;
    foreach (QString switchNumber, path.split(","))
    {
        decodedPath.append(switchNumber.toInt());
    }
    return decodedPath;
}

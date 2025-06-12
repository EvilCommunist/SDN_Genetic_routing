#include "pathsgetter.h"

QVector<QVector<int> > PathsGetter::get(QString paths)
{
    QVector<QVector<int>> pathsVector;
    foreach (QString path, paths.split(";"))
    {
        QVector<int> pathVector;
        foreach (QString switchNumber, path.split(","))
        {
            pathVector.append(switchNumber.toInt());
        }
        pathsVector.append(pathVector);
    }
    return pathsVector;
}

#ifndef GENETICCONTROLLERGENERATOR_H
#define GENETICCONTROLLERGENERATOR_H

#include <QString>
#include <QMap>

class GeneticControllerGenerator
{
public:
    static QString generateGeneticAlgorithmScript(
        int populationSize,
        double crossoverProbability,
        double mutationRate,
        int maxGenerations,
        int earlyStopGen);

    static bool saveScript(const QString& script, const QString& filename);
};

#endif // GENETICCONTROLLERGENERATOR_H

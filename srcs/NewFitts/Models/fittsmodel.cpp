#include "fittsmodel.h"

#include <QDebug>

QSettings FittsModel::DISK("NewFitts", "config");

FittsModel::FittsModel()
    : config({0.20, 0.10, 15, 20, 150}), stats({1, 2, 3, 4, std::list<qint64>(), std::list<qint64>(), std::list<double>(), std::list<double>()})
{
    config.a = DISK.value("a").toDouble();
    config.a = config.a == 0 ? 0.20 : config.a;
    config.b = DISK.value("b").toDouble();
    config.b = config.b == 0 ? 0.10 : config.b;
    config.maxSize = DISK.value("maxSize").toInt();
    config.maxSize = config.maxSize == 0 ? 150 : config.maxSize;
    config.minSize = DISK.value("minSize").toInt();
    config.minSize = config.minSize == 0 ? 20 : config.minSize;
    config.nbPoint = DISK.value("nbPoint").toInt();
    config.nbPoint = config.nbPoint == 0 ? 15 : config.nbPoint;
}

FittsModel::~FittsModel() {
    DISK.setValue("a", config.a);
    DISK.setValue("b", config.b);
    DISK.setValue("maxSize", config.maxSize);
    DISK.setValue("minSize", config.minSize);
    DISK.setValue("nbPoint", config.nbPoint);
}

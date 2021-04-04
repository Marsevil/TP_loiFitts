#ifndef FITTSMODEL_H
#define FITTSMODEL_H

#include <list>
#include <QDebug>

struct Config {
    double a;
    double b;
    unsigned nbPoint;
    unsigned minSize;
    unsigned maxSize;
};

struct Stats {
    double ecartType;
    double erreurType;
    double diffMoy;
    double itc95;
    std::list<double> times;
    std::list<double> distances;
};

class FittsModel
{
    Config config;
    Stats stats;

public:
    FittsModel();

    inline Config const& getConfig() const { return config; }
    inline Stats const& getStats() const { return stats; }

    inline void setConfig(Config _config) { config = _config; }
    inline void setStats(Stats _stats) { stats = _stats; }
};

#endif // FITTSMODEL_H

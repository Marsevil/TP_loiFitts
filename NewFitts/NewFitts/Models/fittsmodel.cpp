#include "fittsmodel.h"

FittsModel::FittsModel()
    : config({0.20, 0.10, 10, 10, 150}), stats({0, 0, 0, 0, std::list<double>(), std::list<double>()})
{
    for (size_t i = 0; i < config.nbPoint; ++i) {
        stats.times.push_back(200);
        stats.distances.push_back(50);
    }
}

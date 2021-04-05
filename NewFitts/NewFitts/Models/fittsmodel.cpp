#include "fittsmodel.h"

FittsModel::FittsModel()
    : config({0.20, 0.10, 10, 10, 150}), stats({1, 2, 3, 4, std::list<double>(), std::list<double>(), std::list<double>()})
{
    for (size_t i = 0; i < config.nbPoint; ++i) {
        stats.times.push_back(100 * i%3);
        stats.distances.push_back(50 * i%2);
        stats.sizes.push_back(10);
    }
}

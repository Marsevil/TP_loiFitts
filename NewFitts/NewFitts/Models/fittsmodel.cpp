#include "fittsmodel.h"

FittsModel::FittsModel()
    : config({0.20, 0.10, 10, 10, 150}), stats({0, 0, 0, 0, std::list<std::size_t>(), std::list<double>()})
{

}

#include "FittsModel.h"
#include "../View/FittsView.h"

FittsModel::FittsModel() {
    this->fittsView = new FittsView(this);
}

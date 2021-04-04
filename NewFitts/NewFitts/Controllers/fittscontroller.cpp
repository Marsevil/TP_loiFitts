#include "fittscontroller.h"

FittsController::FittsController(FittsModel* _model) : model(_model), mainWindow(nullptr)
{
    mainWindow = new MainWindow(this, model);

    run();
}

FittsController::~FittsController() {
    delete mainWindow;
}

void FittsController::run() {
    mainWindow->show();
}

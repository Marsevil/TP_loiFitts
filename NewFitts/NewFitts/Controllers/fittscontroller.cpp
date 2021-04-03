#include "fittscontroller.h"

FittsController::FittsController() : mainWindow(nullptr)
{
    mainWindow = new MainWindow();

    run();
}

FittsController::~FittsController() {
    delete mainWindow;
}

void FittsController::run() {
    mainWindow->show();
}

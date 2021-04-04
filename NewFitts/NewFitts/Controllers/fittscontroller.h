#ifndef FITTSCONTROLLER_H
#define FITTSCONTROLLER_H

#include "../Views/mainwindow.h"
#include "../Models/fittsmodel.h"

class FittsController
{
    FittsModel* model;
    MainWindow* mainWindow;

    void run();
public:
    FittsController(FittsModel* _model);
    ~FittsController();
};

#endif // FITTSCONTROLLER_H

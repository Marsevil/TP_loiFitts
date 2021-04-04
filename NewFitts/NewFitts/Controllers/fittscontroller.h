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

    void cancelConfig() const;
    void updateConfig(Config _config) const;
};

#endif // FITTSCONTROLLER_H

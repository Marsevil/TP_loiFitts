#ifndef FITTSCONTROLLER_H
#define FITTSCONTROLLER_H

#include "../Views/mainwindow.h"

class FittsController
{
    MainWindow* mainWindow;

    void run();
public:
    FittsController();
    ~FittsController();
};

#endif // FITTSCONTROLLER_H

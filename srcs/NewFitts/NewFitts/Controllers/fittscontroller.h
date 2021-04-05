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
    void launchTest(int _sceneWidth, int _sceneHeight, std::list<QPoint>& coordList, std::list<double>& sizeList);
    void finishTest(std::list<qint64> const& times);

    std::list<QPoint> points;
    std::list<double> sizes;
};

#endif // FITTSCONTROLLER_H

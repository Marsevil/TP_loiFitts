#include "fittscontroller.h"

FittsController::FittsController(FittsModel* _model) : model(_model), mainWindow(nullptr)
{
    mainWindow = new MainWindow(this, model);

    run();
}

FittsController::~FittsController() {
    delete mainWindow;
    delete model;
}

void FittsController::run() {
    mainWindow->show();
}

void FittsController::cancelConfig() const {
    mainWindow->setTestView();
}

void FittsController::updateConfig(Config _config) const {
    model->setConfig(_config);
    mainWindow->setTestView();
}


void FittsController::launchTest(int _sceneWidth, int _sceneHeight, std::list<QPoint>& coordList, std::list<double>& sizeList)
{
    // Génération des positions où vont apparaître les cibles du test

    int sceneWidth = _sceneWidth;
    int sceneHeight = _sceneHeight;


    for(uint i = 0; i < model->getConfig().nbPoint; i++)
    {
        // Génération de la taille de la cible
        int size = QRandomGenerator::global()->generate() % ((model->getConfig().maxSize + 1) - model->getConfig().minSize) + model->getConfig().minSize;
        sizeList.push_back(size);

        // Génération des coordonnées de la cible
        double posX = QRandomGenerator::global()->generate() % ((sceneWidth - size) - size) + size;
        double posY = QRandomGenerator::global()->generate() % ((sceneHeight - size) - size) + size;
        QPoint coord(posX, posY);
        coordList.push_back(coord);
    }


}

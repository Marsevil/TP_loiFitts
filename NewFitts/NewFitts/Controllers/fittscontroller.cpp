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

    sizes = sizeList;
    points = coordList;
    points.push_front(QPoint(sceneWidth/2, sceneHeight/2));
}

void FittsController::finishTest(std::list<qint64> const& times) {
    std::list<double> distances;

    std::list<QPoint>::const_iterator point = points.begin();
    for (std::size_t i = 0; i < points.size()-1; ++i) {
        QPoint P1 = *(point++);
        QPoint P2 = *(point++);

        distances.push_back(sqrt(pow(P2.x() - P1.x(), 2) + pow(P2.y() - P1.y(), 2)));
    }

    points.clear();
    model->setStats({0, 0, 0, 0, times, distances, sizes});
}

#include "mainwindow.h"
#include "../Controllers/fittscontroller.h"

MainWindow::MainWindow(FittsController* _controller, FittsModel const* _model, QWidget *parent)
    : QMainWindow(parent), controller(_controller), model(_model)
{
    setTestView();

    QAction* quit = new QAction("Quitter");
    QAction* settings = new QAction("Options");
    menuBar()->setNativeMenuBar(false);
    QMenu* viewMenu = menuBar()->addMenu("Fichier");
    viewMenu->addAction(settings);
    viewMenu->addAction(quit);

    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(settings, SIGNAL(triggered()), this, SLOT(setConfigView()));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setTestView()
{
    TestView* view = new TestView(this);
    setCentralWidget(view);

    connect(view, SIGNAL(startTest(int,int)), this, SLOT(launchTest(int,int)));
    connect(this, SIGNAL(executeTest(std::list<QPoint>,std::list<double>)), view, SLOT(executeTestHandler(std::list<QPoint>,std::list<double>)));
    connect(view, SIGNAL(endTest(std::list<qint64>)), this, SLOT(finishTest(std::list<qint64>)));
}

void MainWindow::setGraphView() {
    GraphView* view = new GraphView(model->getConfig(), model->getStats(), this);
    setCentralWidget(view);

    connect(view, SIGNAL(quit()), qApp, SLOT(quit()));
    connect(view, SIGNAL(restart()), this, SLOT(setTestView()));
}

void MainWindow::setConfigView() {
    ConfigView* view = new ConfigView(model->getConfig(), this);
    view->move(width()/2 - view->width()/2, height()/2 - view->height()/2);

    setCentralWidget(view);

    connect(view, SIGNAL(cancel()), this, SLOT(configCancel()));
    connect(view, SIGNAL(confirm(Config)), this, SLOT(updateConfig(Config)));
}

void MainWindow::configCancel() {
    setTestView();
}

void MainWindow::updateConfig(Config _config) {
    controller->updateConfig(_config);
    setTestView();
}

void MainWindow::launchTest(int _sceneWidth, int _sceneHeight)
{
    // Génération de listes vides de points et de tailles de cercle
    std::list<QPoint> coordList;
    std::list<double> sizeList;

    // Requête au contrôleur pour remplir les listes
    controller->launchTest(_sceneWidth, _sceneHeight, coordList, sizeList);

    // Envoi des listes à la TestView
    emit executeTest(coordList, sizeList);
}

void MainWindow::finishTest(std::list<qint64> const& times) {
    controller->finishTest(times);
    setGraphView();
}

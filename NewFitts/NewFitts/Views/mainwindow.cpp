#include "mainwindow.h"

#include "../Controllers/fittscontroller.h"

#include <QAction>
#include <QMenuBar>

MainWindow::MainWindow(FittsController* _controller, FittsModel const* _model, QWidget *parent)
    : QMainWindow(parent), controller(_controller), model(_model)
{
    setConfigView();

    QAction* setTest = new QAction("Test View");
    QAction* setGraph = new QAction("Graph View");
    QAction* setConfig = new QAction("Config View");
    menuBar()->setNativeMenuBar(false);
    QMenu* viewMenu = menuBar()->addMenu("Views");
    viewMenu->addAction(setTest);
    viewMenu->addAction(setConfig);
    viewMenu->addAction(setGraph);

    connect(setTest, SIGNAL(triggered()), this, SLOT(setTestView()));
    connect(setGraph, SIGNAL(triggered()), this, SLOT(setGraphView()));
    connect(setConfig, SIGNAL(triggered()), this, SLOT(setConfigView()));

    adjustSize();

}

MainWindow::~MainWindow()
{

}

void MainWindow::setTestView()
{
    resize(900, 800);
    TestView* view = new TestView(this);
    setCentralWidget(view);

    connect(view, SIGNAL(startTest(int, int)), this, SLOT(launchTest(int, int)));
    connect(this, SIGNAL(executeTest(std::list<QPoint>, std::list<double>)), view, SLOT(executeTestHandler(std::list<QPoint>, std::list<double>)));
    connect(view, SIGNAL(endTest(std::list<qint64>)), this, SLOT(finishTest(std::list<qint64>)));
}

void MainWindow::setGraphView() {
    setCentralWidget(new GraphView(model->getConfig(), model->getStats(), this));
    adjustSize();
}

void MainWindow::setConfigView() {
    ConfigView* view = new ConfigView(model->getConfig(), this);
    setCentralWidget(view);
    adjustSize();

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

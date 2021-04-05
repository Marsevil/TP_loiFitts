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

void MainWindow::setTestView() {
    setCentralWidget(new TestView(this));
    adjustSize();
}

void MainWindow::setGraphView() {
    setCentralWidget(new GraphView(this));
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

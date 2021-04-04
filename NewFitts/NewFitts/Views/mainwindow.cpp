#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>

MainWindow::MainWindow(FittsController* _controller, FittsModel* _model, QWidget *parent)
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


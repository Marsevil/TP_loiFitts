#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setTestView();

    QAction* setTest = new QAction("Test View");
    QAction* setGraph = new QAction("Graph View");
    QAction* setConfig = new QAction("Config View");
    QMenu* viewMenu = menuBar()->addMenu("Views");
    viewMenu->addAction(setTest);
    viewMenu->addAction(setGraph);
    viewMenu->addAction(setConfig);

    connect(setTest, SIGNAL(triggered()), this, SLOT(setTestView()));
    connect(setGraph, SIGNAL(triggered()), this, SLOT(setGraphView()));
    connect(setConfig, SIGNAL(triggered()), this, SLOT(setConfigView()));
}

MainWindow::~MainWindow()
{

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "testview.h"
#include "graphview.h"
#include "configview.h"

class FittsModel;
class FittsController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    FittsController* controller;
    FittsModel const* model;

public:
    MainWindow(FittsController* _controller, FittsModel const* _model, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    inline void setTestView() { setCentralWidget(new TestView); adjustSize(); }
    inline void setGraphView() { setCentralWidget(new GraphView); adjustSize(); }
    inline void setConfigView() { setCentralWidget(new ConfigView(model->getConfig(), controller)); adjustSize(); }
};
#endif // MAINWINDOW_H

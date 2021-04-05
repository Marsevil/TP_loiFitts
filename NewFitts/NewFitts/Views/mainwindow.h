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
    void setTestView();
    void setGraphView();
    void setConfigView();

private slots:
    void configCancel();
    void updateConfig(Config);
};
#endif // MAINWINDOW_H

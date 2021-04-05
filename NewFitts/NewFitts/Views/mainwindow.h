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
    void launchTest(int _sceneWidth, int _sceneHeight);
    void finishTest(std::list<qint64> const&);

signals:
    void executeTest(std::list<QPoint>, std::list<double> const&) const;
};
#endif // MAINWINDOW_H

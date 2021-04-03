#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "testview.h"
#include "graphview.h"
#include "configview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    inline void setTestView() { setCentralWidget(new TestView); adjustSize(); }
    inline void setGraphView() { setCentralWidget(new GraphView); adjustSize(); }
    inline void setConfigView() { setCentralWidget(new ConfigView); adjustSize(); }
};
#endif // MAINWINDOW_H

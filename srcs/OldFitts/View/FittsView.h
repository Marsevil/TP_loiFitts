#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GraphicWidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStackedLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QLineSeries>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

class FittsModel;
class FittsController;

class FittsView : public QMainWindow
{
    Q_OBJECT
public:
    FittsView(FittsController* _controller, FittsModel* _model);
    ~FittsView();
    void initWindows();
    void updateTestMsg();
    void displayResults();

    void setMainStackIndex(int _index) {mainStack->setCurrentIndex(_index);}
    void setResultButtonEnabled(bool _bool) {resultBtn->setEnabled(_bool);}
    void setGraphicViewEnabled(bool _bool) {graphicView->setEnabled(_bool);}
    void setPlotChart(QChart* _chart) {plot->setChart(_chart);}
    void setPlotRenderHint(QPainter::RenderHint _option) {plot->setRenderHint(_option);}


    QPointF getGraphicViewMapToScene(int _x, int _y) {return graphicView->mapToScene(_x,_y);}
    int getGraphicViewWidth() {return graphicView->width();}
    int getGraphicViewHeight() {return graphicView->height();}
    QGraphicsScene* getScene() {return scene;}



private:

    FittsController* fittsController;
    FittsModel* fittsModel;

    QPushButton *leaveBtn;
    QPushButton *startBtn;
    QPushButton *backBtn;
    QPushButton *resultBtn;
    QPushButton *resultLeaveBtn;
    QPushButton *restartBtn;

    QDoubleSpinBox *aValue;
    QDoubleSpinBox *bValue;
    QSpinBox *nbCible;
    QSpinBox *minSize;
    QSpinBox *maxSize;

    QStackedLayout *mainStack;

    GraphicWidget *graphicView;
    QGraphicsScene *scene;

    QLabel *testLabel;
    QLabel *ecartType;
    QLabel *erreurType;
    QLabel *diffMoy;
    QLabel *itc95;

    QChartView *plot;

};

#endif // MAINWINDOW_H

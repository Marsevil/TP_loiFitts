#ifndef TESTVIEW_H
#define TESTVIEW_H

#include "detectclick.h"

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QGraphicsView>
#include <QChartView>
#include <QVBoxLayout>
#include <QtCharts>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>

class TestView : public QWidget
{
    Q_OBJECT
    QGraphicsScene* scene;
    QPushButton* startButton;
    QGraphicsEllipseItem* ellipse;
    DetectClick* graphicView;

    QElapsedTimer* timer;
    QPointF firstClick;

    std::list<QPoint> coordList;
    std::list<double> sizeList;
    std::list<qint64> elapsedTimes;

    void showCible();
public:
    explicit TestView(QWidget *parent = nullptr);

private slots:
    void startTestButtonHandler();
    void executeTestHandler(std::list<QPoint> _coordList, std::list<double> _sizeList);
    void cibleClicked(int, int);

signals:
    void startTest(int, int) const;
    void endTest(std::list<qint64> const&) const;
};

#endif // TESTVIEW_H

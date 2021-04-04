#ifndef TESTVIEW_H
#define TESTVIEW_H

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
public:
    explicit TestView(QWidget *parent = nullptr);

signals:

};

#endif // TESTVIEW_H

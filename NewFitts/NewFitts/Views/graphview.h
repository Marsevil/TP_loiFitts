#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

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

class GraphView : public QWidget
{
    Q_OBJECT
public:
    explicit GraphView(QWidget *parent = nullptr);

private:


signals:

};

#endif // GRAPHVIEW_H

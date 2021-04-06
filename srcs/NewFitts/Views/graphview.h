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

#include "../Models/fittsmodel.h"

class GraphView : public QWidget
{
    Q_OBJECT
public:
    explicit GraphView(Config const& config, Stats const& stats, QWidget *parent = nullptr);

private:

private slots:
    inline void quitButtonHandler() const { emit quit(); }
    inline void restartButtonHandler() const { emit restart(); }

signals:
    void quit() const;
    void restart() const;
};

#endif // GRAPHVIEW_H

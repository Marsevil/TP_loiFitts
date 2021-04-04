#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSvgWidget>
#include <QPushButton>

#include "../Models/fittsmodel.h"

class FittsController;

class ConfigView : public QWidget
{
    Q_OBJECT

    int const MAX_MIN_RANGE = 250;

    FittsController* controller;
    Config config;

public:
    explicit ConfigView(Config _config, FittsController* _controller, QWidget *parent = nullptr);

private slots:
    inline void updateA(double _a) { config.a = _a; }
    inline void updateB(double _b) { config.b = _b; }
    inline void updateMinSize(int _minSize) { config.minSize = (unsigned)_minSize; }
    inline void updateMaxSize(int _maxSize) { config.maxSize = (unsigned)_maxSize; }
    inline void updateNbPoint(int _nbPoint) { config.nbPoint = (unsigned)_nbPoint; }

    void cancelPressed() const;
    void confirmPressed() const;
};

#endif // CONFIGVIEW_H

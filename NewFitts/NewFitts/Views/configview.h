#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QWidget>
#include <QDebug>

#include "../Models/fittsmodel.h"

class ConfigView : public QWidget
{
    Q_OBJECT

    int const MAX_MIN_RANGE = 250;

    Config config;

public:
    explicit ConfigView(Config _config, QWidget *parent = nullptr);

private slots:
    inline void updateA(double _a) { config.a = _a; }
    inline void updateB(double _b) { config.b = _b; }
    inline void updateMinSize(int _minSize) { config.minSize = (unsigned)_minSize; }
    inline void updateMaxSize(int _maxSize) { config.maxSize = (unsigned)_maxSize; }
    inline void updateNbPoint(int _nbPoint) { config.nbPoint = (unsigned)_nbPoint; }

    inline void cancelPressed() { qDebug() << "Cancel pressed !!"; }
    inline void confirmPressed() { qDebug() << "a = " << config.a
                                            << " b = " << config.b
                                            << " minSize = " << config.minSize
                                            << " maxSize = " << config.maxSize
                                            << " nbPoint = " << config.nbPoint; }

signals:
    void cancel();
    void confirm(Config);
};

#endif // CONFIGVIEW_H

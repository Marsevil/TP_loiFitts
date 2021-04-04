#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QWidget>

#include "../Models/fittsmodel.h"

class ConfigView : public QWidget
{
    Q_OBJECT

    int const MAX_MIN_RANGE = 250;

    Config config;

public:
    explicit ConfigView(Config _config, QWidget *parent = nullptr);

signals:

};

#endif // CONFIGVIEW_H

#include "configview.h"

#include <QVBoxLayout>
#include <QLabel>

ConfigView::ConfigView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Config View", this));
}

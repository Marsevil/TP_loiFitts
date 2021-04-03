#include "graphview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

GraphView::GraphView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Graph View", this));
}

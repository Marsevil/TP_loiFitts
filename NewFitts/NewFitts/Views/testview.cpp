#include "testview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

TestView::TestView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Test view", this));
}

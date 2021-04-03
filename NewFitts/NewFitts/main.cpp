#include <QApplication>

#include "Controllers/fittscontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FittsController controller;

    return a.exec();
}

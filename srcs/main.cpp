#include "Model/FittsModel.h"
#include "Controller/FittsController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    FittsModel* fittsModel = new FittsModel;
    FittsController* fittsController = new FittsController(fittsModel);

    return a.exec();
}

#include <QApplication>

#include "Controllers/fittscontroller.h"
#include "Models/fittsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FittsModel* fittsModel = new FittsModel;
    FittsController controller(fittsModel);

    return a.exec();
}

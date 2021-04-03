#ifndef FITTSMODEL_H
#define FITTSMODEL_H

#include <QPoint>
#include <QList>

class FittsController;
class FittsView;

class FittsModel
{
public:
    FittsModel();

    inline int getCibleLeft() {return cibleLeft;}
    inline int getNbCible() {return nbCible;}
    inline int getMinSize() {return minSize;}
    inline int getMaxSize() {return maxSize;}

    inline double getA() {return a;}
    inline double getB() {return b;}

    inline double getEcartType() {return ecartType;}
    inline double getErreurType() {return erreurType;}
    inline double getDiffMoy() {return diffMoy;}
    inline double getItc95() {return itc95;}

private:
    int cibleLeft = 0;
    int nbCible = 10;
    int minSize = 10;
    int maxSize = 150;

    double a = 0.20;
    double b = 0.10;

    double ecartType = 0;
    double erreurType = 0;
    double diffMoy = 0;
    double itc95 = 0;

    QList<QPoint> clickPoints;
    QList<QPoint> cercleCenter;
    QList<int> cercleSize;
    QList<qint64> times;

    friend FittsController;
};

#endif // FITTSMODEL_H

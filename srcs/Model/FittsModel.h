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

    inline int getCibleLeft() const {return cibleLeft;}
    inline int getNbCible() const {return nbCible;}
    inline int getMinSize() const {return minSize;}
    inline int getMaxSize() const {return maxSize;}

    inline double getA() const {return a;}
    inline double getB() const {return b;}

    inline double getEcartType() const {return ecartType;}
    inline double getErreurType() const {return erreurType;}
    inline double getDiffMoy() const {return diffMoy;}
    inline double getItc95() const {return itc95;}

    inline QList<QPoint> const& getClickPoints() const {return clickPoints;}
    inline QList<QPoint> const& getCercleCenter() const {return cercleCenter;}
    inline QList<int> const& getCercleSize() const {return cercleSize;}
    inline QList<qint64> const& getTimes() const {return times;}


    inline void setCibleLeft(int _cibleLeft) {cibleLeft = _cibleLeft;}
    inline void setNbCible(int _nbCible) {nbCible = _nbCible;}
    inline void setMinSize(int _minSize) {minSize = _minSize;}
    inline void setMaxSize(int _maxSize) {maxSize = _maxSize;}

    inline void setA(double _a) {a = _a;}
    inline void setB(double _b) {b = _b;}

    inline void setEcartType(double _ecartType) {ecartType = _ecartType;}
    inline void setErreurType(double _erreurType) {erreurType = _erreurType;}
    inline void setDiffMoy(double _diffMoy) {diffMoy = _diffMoy;}
    inline void setItc95(double _itc95) {itc95 = _itc95;}

    inline void clearCercleSize() {cercleSize.clear();}
    inline void clearCercleCenter() {cercleCenter.clear();}
    inline void clearClickPoints() {clickPoints.clear();}
    inline void clearTimes() {times.clear();}

    inline void appendCercleSize(int _size) {cercleSize.append(_size);}
    inline void appendCercleCenter(QPoint _pos) {cercleCenter.append(_pos);}
    inline void appendClickPoints(QPoint _pos) {clickPoints.append(_pos);}
    inline void appendTimes(qint64 _time) {times.append(_time);}



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

};

#endif // FITTSMODEL_H

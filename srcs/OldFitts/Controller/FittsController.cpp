#include "FittsController.h"
#include "../View/FittsView.h"
#include "../Model/FittsModel.h"

#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalBarSeries>
#include <QCategoryAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QStringList>
#include <QElapsedTimer>

QT_CHARTS_USE_NAMESPACE

FittsController::FittsController(FittsModel* _fittsModel) : fittsModel(_fittsModel), fittsView(nullptr) {
    fittsView = new FittsView(this, fittsModel);
    this->start();
}

void FittsController::start() {
    this->fittsView->show();
}

void FittsController::startSimulation() {
    this->fittsView->setMainStackIndex(1);
    this->fittsModel->setCibleLeft(this->fittsModel->getNbCible());
    this->fittsView->updateTestMsg();
    this->fittsView->setResultButtonEnabled(false);
    this->fittsView->setGraphicViewEnabled(true);
    this->fittsModel->clearCercleSize();
    this->fittsModel->clearCercleCenter();
    this->fittsModel->clearClickPoints();
    this->fittsModel->clearTimes();

    this->initGame();
}

void FittsController::quit() {
    QApplication::quit();
}

void FittsController::backToSettings() {
    this->fittsView->setMainStackIndex(0);
}
void FittsController::resultClicked() {
    this->fittsView->setMainStackIndex(2);

    this->calculateResult();
}
void FittsController::aValueChanged(double value) {
    this->fittsModel->setA(value);
}
void FittsController::bValueChanged(double value) {
    this->fittsModel->setB(value);
}
void FittsController::nbCibleChanged(int value) {
    this->fittsModel->setNbCible(value);
}
void FittsController::minSizeChanged(int value) {
    this->fittsModel->setMinSize(value);
}
void FittsController::maxSizeChanged(int value) {
    this->fittsModel->setMaxSize(value);
}
void FittsController::cibleClicked(int x, int y) {
    if(this->fittsModel->getCercleCenter().isEmpty()) {
        // Si vide alors premier click, on demarre le timer
        this->timer = new QElapsedTimer;
        timer->start();

        // On démarre avec la première cible
        this->fittsModel->appendClickPoints(QPoint(x,y));
        this->nextCible();
    }
    else {
        QPointF coords = this->fittsView->getGraphicViewMapToScene(x,y);
        if(sqrt(pow(coords.x() - this->fittsModel->getCercleCenter().last().x(),2) + pow(coords.y() - this->fittsModel->getCercleCenter().last().y(),2)) <= this->fittsModel->getCercleSize().last() / 2) {
            // On stock le temps de click
            this->fittsModel->appendTimes(timer->elapsed());
            // On restart le chrono
            timer->restart();

            // On stock la position du click
            this->fittsModel->appendClickPoints(QPoint(x,y));
            this->nextCible();
        }
    }
}

void FittsController::nextCible() {
    if(!this->fittsModel->getCercleCenter().isEmpty())
        this->fittsModel->setCibleLeft(this->fittsModel->getCibleLeft() - 1);
    this->fittsView->updateTestMsg();

    QGraphicsScene *scene = this->fittsView->getScene();
    scene->clear();

    // On stop si c'est finis
    if(this->fittsModel->getCibleLeft() == 0) {
        this->finish();
        return;
    }

    // On génère la taille du cercle rouge
    // qrand() % ((high + 1) - low) + low;
    int size = qrand() % ((this->fittsModel->getMaxSize() + 1) - this->fittsModel->getMinSize()) + this->fittsModel->getMinSize();
    // Car on veut le rayon
    // On place le cercle dans la scene (Attention faut pas qu'il soit en dehors du cadre)
    int sceneW = int(scene->width());
    int sceneH = int(scene->height());

    qreal posX = qrand() % ((sceneW - size) - size) + size;
    qreal posY = qrand() % ((sceneH - size) - size) + size;

    // On stock les infos sur le cercle
    this->fittsModel->appendCercleCenter(QPoint(int(posX),int(posY)));
    this->fittsModel->appendCercleSize(size);

    // On place le cercle
    scene->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor("red")),QBrush(QColor("red")));
}


void FittsController::finish() {
    this->fittsView->setGraphicViewEnabled(false);
    this->fittsView->setResultButtonEnabled(true);
}

void FittsController::initGame() {
    QGraphicsScene *scene = this->fittsView->getScene();
    scene->clear();

    if(this->fittsModel->getMaxSize() >= this->fittsView->getGraphicViewWidth() / 2)
        this->fittsModel->setMaxSize(this->fittsView->getGraphicViewWidth() / 2);

    if(this->fittsModel->getMaxSize() >= this->fittsView->getGraphicViewHeight() / 2)
        this->fittsModel->setMaxSize(this->fittsView->getGraphicViewHeight() / 2);

    qreal posX = scene->width() / 2;
    qreal posY = scene->height() / 2;
    int size = 100;

    scene->addEllipse(posX - (size / 2), posY - (size / 2), size, size, QPen(QColor("blue")),QBrush(QColor("blue")));
}

void FittsController::calculateResult() {
    QChart *chart = new QChart;

    this->fittsView->setPlotChart(chart);
    this->fittsView->setPlotRenderHint(QPainter::Antialiasing);
    chart->setTitle("Résultats loi Fitts");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries *expSeries = new QLineSeries;
    expSeries->setName("Courbe expérimentale");
    QLineSeries *fittsSeries = new QLineSeries;
    fittsSeries->setName("Courbe théorique");
    QCategoryAxis *axis = new QCategoryAxis;

    QList<double> fittsValues;

    for(int i = 0; i < this->fittsModel->getNbCible(); ++i) {
        double T = this->fittsModel->getTimes()[i];
        expSeries->append(i,T);
        double D = sqrt(pow(this->fittsModel->getClickPoints()[i].x() - this->fittsModel->getCercleCenter()[i].x(),2) + pow(this->fittsModel->getClickPoints()[i].y() - this->fittsModel->getCercleCenter()[i].y(),2));

        // On multiplie par 100 pour être en ms
        double value = (this->fittsModel->getA() * 1000) + ((this->fittsModel->getB() * 1000) * log2((D / this->fittsModel->getCercleSize()[i]) + 1));
        fittsValues.append(value);
        fittsSeries->append(i,value);

        axis->append(QString::number(i + 1) + "<br />T: "+QString::number(T)+"<br />D: " + QString::number(D),i);
    }
    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addSeries(expSeries);
    chart->addSeries(fittsSeries);

    chart->setAxisX(axis,expSeries);
    chart->setAxisX(axis,fittsSeries);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("temps (en ms)");
    chart->setAxisY(axisY,expSeries);



    // Calcul des valeurs
    // Moyennes
    QList<double> diffValues;
    double diffMoy = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        diffValues.append(fabs(fittsValues[i] - this->fittsModel->getTimes()[i]));
        diffMoy += fabs(fittsValues[i] - this->fittsModel->getTimes()[i]);
    }
    diffMoy /= fittsValues.size();

    // On stock la difference de moyenne
    this->fittsModel->setDiffMoy(fabs(diffMoy));


    // Ecart type
    double variance = 0;

    for (int i = 0; i < fittsValues.size(); ++i) {
        variance += pow(diffValues[i] - diffMoy,2);
    }
    variance /= fittsValues.size();

    double ecartType = sqrt(variance);

    // On stock l'ecart type
    this->fittsModel->setEcartType(ecartType);
    // On stock l'erreur type
    this->fittsModel->setErreurType(fabs(ecartType / sqrt(fittsValues.size())));

    // On stock itc 95%
    this->fittsModel->setItc95(2 * this->fittsModel->getErreurType());

    this->fittsView->displayResults();
}

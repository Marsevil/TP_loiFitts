#include "graphview.h"


GraphView::GraphView(Config const& config, Stats const& stats, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignHCenter);

    // Titre
    QWidget* titleBox = new QWidget(this);
    QLayout* titleBoxLayout = new QVBoxLayout(titleBox);
    titleBoxLayout->setAlignment(Qt::AlignHCenter);
    QLabel* title = new QLabel("Résultats", this);
    QFont titleFont("Calibri", 20, QFont::Bold);
    title->setFont(titleFont);
    titleBoxLayout->addWidget(title);
    titleBox->setLayout(titleBoxLayout);
    mainLayout->addWidget(titleBox);

    // Graph
    QWidget* graphBox = new QWidget(this);
    QLayout* graphBoxLayout = new QVBoxLayout(graphBox);
    graphBoxLayout->setAlignment(Qt::AlignHCenter);

    QGraphicsView* graphicView = new QGraphicsView(graphBox);
    graphBoxLayout->addWidget(graphicView);
    graphicView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    graphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsScene* scene = new QGraphicsScene(graphicView);
    graphicView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    graphicView->setScene(scene);
    scene->setSceneRect(0,0,graphicView->width(),300);

    mainLayout->addWidget(graphBox);

    // Statistiques
    QWidget* statBox = new QWidget(this);
    QLayout* statLayout = new QHBoxLayout(statBox);
    statBox->setLayout(statLayout);
    statLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(statBox);

    // Paramètres utilisés
    QGroupBox* parametreBox = new QGroupBox("Paramètres de l'expérience");
    statLayout->addWidget(parametreBox);

    QLayout* parametreLayout = new QVBoxLayout();
    parametreBox->setLayout(parametreLayout);

    QLabel* aLabel = new QLabel("Valeur de a : " + QString::number(config.a), parametreBox);
    parametreLayout->addWidget(aLabel);

    QLabel* bLabel = new QLabel("Valeur de b : " + QString::number(config.b), parametreBox);
    parametreLayout->addWidget(bLabel);

    QLabel* nbCibleLabel = new QLabel("Nombre de cibles : " + QString::number(config.nbPoint), parametreBox);
    parametreLayout->addWidget(nbCibleLabel);

    QLabel* tailleIntervalleLabel = new QLabel("Intervalle de taille des cibles : " + QString::number(config.maxSize - config.minSize), parametreBox);
    parametreLayout->addWidget(tailleIntervalleLabel);


    // Résultats du test
    QGroupBox* resultatBox = new QGroupBox("Résultats de l'expérience");
    statLayout->addWidget(resultatBox);

    QLayout* resultatLayout = new QVBoxLayout();
    resultatBox->setLayout(resultatLayout);

    QLabel* ecartTypeLabel = new QLabel("Ecart-Type : " + QString::number(stats.ecartType), resultatBox);
    resultatLayout->addWidget(ecartTypeLabel);

    QLabel* erreurTypeLabel = new QLabel("Erreur-Type : " + QString::number(stats.erreurType), resultatBox);
    resultatLayout->addWidget(erreurTypeLabel);

    QLabel* differenceLabel = new QLabel("Différence moyenne : " + QString::number(stats.diffMoy), resultatBox);
    resultatLayout->addWidget(differenceLabel);

    QLabel* intervalleLabel = new QLabel("Intervalle de confiance à 95% : " + QString::number(stats.itc95), resultatBox);
    resultatLayout->addWidget(intervalleLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout(this);
    mainLayout->addItem(btnLayout);

    QPushButton* leaveBtn = new QPushButton("Quitter", this);
    btnLayout->addWidget(leaveBtn);

    QPushButton* restartBtn = new QPushButton("Recommencer", this);
    btnLayout->addWidget(restartBtn);
}

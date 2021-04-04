#include "graphview.h"


GraphView::GraphView(QWidget *parent) : QWidget(parent)
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

    QGraphicsView* graphicView = new QGraphicsView;
    graphBoxLayout->addWidget(graphicView);
    graphicView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    graphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsScene* scene = new QGraphicsScene;
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

    QLabel* aLabel = new QLabel("Valeur de a : ");
    parametreLayout->addWidget(aLabel);
    //a = new QLabel;
    //parametreLayout->addWidget(a);

    QLabel* bLabel = new QLabel("Valeur de b : ");
    parametreLayout->addWidget(bLabel);
    //b = new QLabel;
    //parametreLayout->addWidget(b);

    QLabel* nbCibleLabel = new QLabel("Nombre de cibles : ");
    parametreLayout->addWidget(nbCibleLabel);
    //nbCible = new QLabel;
    //parametreLayout->addWidget(nbCible);

    QLabel* tailleIntervalleLabel = new QLabel("Intervalle de taille des cibles : ");
    parametreLayout->addWidget(tailleIntervalleLabel);
    //range = new QLabel;
    //range = tailleMax - tailleMin;
    //parametreLayout->addWidget(range);


    // Résultats du test
    QGroupBox* resultatBox = new QGroupBox("Résultats de l'expérience");
    statLayout->addWidget(resultatBox);

    QLayout* resultatLayout = new QVBoxLayout();
    resultatBox->setLayout(resultatLayout);

    QLabel* ecartTypeLabel = new QLabel("Ecart-Type : ");
    resultatLayout->addWidget(ecartTypeLabel);
    //ecartType = new QLabel;
    //resultBoxLayout->addWidget(ecartType,0,1);

    QLabel* erreurTypeLabel = new QLabel("Erreur-Type : ");
    resultatLayout->addWidget(erreurTypeLabel);
    //erreurType = new QLabel;
    //resultBoxLayout->addWidget(erreurType,1,1);

    QLabel* differenceLabel = new QLabel("Différence moyenne : ");
    resultatLayout->addWidget(differenceLabel);
    //diffMoy = new QLabel;
    //resultBoxLayout->addWidget(diffMoy,0,3);

    QLabel* intervalleLabel = new QLabel("Intervalle de confiance à 95% : ");
    resultatLayout->addWidget(intervalleLabel);
    //itc95 = new QLabel;
    //resultBoxLayout->addWidget(itc95,1,3);

     /*
    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnLayout = new QHBoxLayout;
    resultLayout->addLayout(btnLayout);

    resultLeaveBtn = new QPushButton("Quitter");
    btnLayout->addWidget(resultLeaveBtn);

    restartBtn = new QPushButton("Recommencer");
    btnLayout->addWidget(restartBtn);
    */
}

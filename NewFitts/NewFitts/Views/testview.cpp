#include "testview.h"


TestView::TestView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mainLayout->setAlignment(Qt::AlignHCenter);

    // Titre
    QWidget* titleBox = new QWidget(this);
    QLayout* titleBoxLayout = new QVBoxLayout(titleBox);
    titleBoxLayout->setAlignment(Qt::AlignHCenter);
    QLabel* title = new QLabel("Expérience", this);
    QFont titleFont("Calibri", 20, QFont::Bold);
    title->setFont(titleFont);
    titleBoxLayout->addWidget(title);
    titleBox->setLayout(titleBoxLayout);
    mainLayout->addWidget(titleBox);

    // Phrase d'explication
    QLabel* label = new QLabel("Cliquez sur Démarrer le test, puis cliquez le plus rapidement possible sur les cibles <font color='red'><strong>rouge</strong></font> qui vont apparaître.");
    label->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(label);


    // Zone de test
    QWidget* testBox = new QWidget(this);
    QLayout* testBoxLayout = new QVBoxLayout(testBox);
    testBoxLayout->setAlignment(Qt::AlignHCenter);

    QGraphicsView* graphicView = new QGraphicsView;
    testBoxLayout->addWidget(graphicView);
    graphicView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    graphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsScene* scene = new QGraphicsScene;
    graphicView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    graphicView->setScene(scene);
    scene->setSceneRect(0,0,graphicView->width(),300);

    mainLayout->addWidget(testBox);

    // Bouton Start Test
    QLayout* sceneLayout = new QVBoxLayout(graphicView);
    QPushButton* startButton = new QPushButton("Démarrer le test");
    sceneLayout->addWidget(startButton);
    sceneLayout->setAlignment(Qt::AlignHCenter);
    startButton->setGeometry(300, 300, 300, 300);

}


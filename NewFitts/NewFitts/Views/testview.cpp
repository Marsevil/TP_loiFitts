#include "testview.h"

#include <QDebug>


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

    scene = new QGraphicsScene;
    graphicView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    graphicView->setScene(scene);
    scene->setSceneRect(0,0,graphicView->width(),300);

    mainLayout->addWidget(testBox);

    // Bouton Start Test
    QLayout* sceneLayout = new QVBoxLayout(graphicView);
    startButton = new QPushButton("Démarrer le test");
    sceneLayout->addWidget(startButton);
    sceneLayout->setAlignment(Qt::AlignHCenter);
    startButton->setGeometry(300, 300, 300, 300);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startTestButtonHandler()));

    // Connect with the class detecting mouse click
    DetectClick* detectClick = new DetectClick;
    connect(this, SIGNAL(mouseClicked(int,int)), detectClick, SLOT(cibleClicked(int,int)));

}

void TestView::startTestButtonHandler()
{
    startButton->setEnabled(false);
    emit startTest(scene->width(), scene->height());
}


void TestView::executeTestHandler(std::list<QPoint> _coordList, std::list<double> _sizeList)
{
    // Récupération de la liste de coordonnées et de tailles de cercle puis affichage à l'écran
    std::list<double>::const_iterator sizeListIterator = _sizeList.begin();

    for (QPoint const& point : _coordList)
    {
        ellipse = scene->addEllipse((point.x() - ((*sizeListIterator) / 2)), point.y() - ((*sizeListIterator) / 2), (*sizeListIterator), (*sizeListIterator), QPen(QColor("red")), QBrush(QColor("red")));
        sizeListIterator++;
    }

}

void TestView::cibleClicked(int x, int y)
{

}


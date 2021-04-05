#include "testview.h"

#include <QDebug>


TestView::TestView(QWidget *parent) : QWidget(parent), timer(nullptr)
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

    graphicView = new DetectClick;
    testBoxLayout->addWidget(graphicView);
    graphicView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    graphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene;
    graphicView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    graphicView->setScene(scene);
    scene->setSceneRect(0,0,graphicView->width(),graphicView->height());

    mainLayout->addWidget(testBox);

    // Bouton Start Test
    QLayout* sceneLayout = new QVBoxLayout(graphicView);
    startButton = new QPushButton("Démarrer le test");
    sceneLayout->addWidget(startButton);
    sceneLayout->setAlignment(Qt::AlignHCenter);
    startButton->setGeometry(300, 300, 300, 300);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startTestButtonHandler()));

    // Connect with the class detecting mouse click
    connect(graphicView, SIGNAL(mouseClicked(int,int)), this, SLOT(cibleClicked(int,int)));

}

void TestView::startTestButtonHandler()
{
    if (timer) {
        emit endTest();
    } else {
        startButton->setVisible(false);
        emit startTest(scene->width(), scene->height());
    }
}


void TestView::executeTestHandler(std::list<QPoint> _coordList, std::list<double> _sizeList)
{
    coordList = _coordList;
    sizeList = _sizeList;
    showCible();
    timer = new QElapsedTimer;
    timer->start();
}

void TestView::cibleClicked(int x, int y)
{
    QPointF coords = graphicView->mapToScene(x,y);

    if (sqrt(pow(coords.x() - coordList.front().x(), 2) + pow(coords.y() - coordList.front().y(), 2)) <= sizeList.front() / 2)
    {
        scene->clear();
        sizeList.pop_front();
        coordList.pop_front();
        showCible();
        elapsedTimes.push_back(timer->elapsed());
        timer->restart();
    }
}

void TestView::showCible()
{
    // Récupération de la liste de coordonnées et de tailles de cercle puis affichage à l'écran

    if (coordList.empty() == true) // Si la liste des coordonnées est vide, on a fini le test
    {
        startButton->setText("Voir les résultats");
        startButton->setVisible(true);
    }
    else // Sinon on re génère un cercle
    {
        scene->addEllipse((coordList.front().x() - ((sizeList.front()) / 2)), coordList.front().y() - ((sizeList.front()) / 2), (sizeList.front()), (sizeList.front()), QPen(QColor("red")), QBrush(QColor("red")));
    }
}


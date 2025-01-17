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

    QWidget* content = new QWidget(this);
    QLayout* contentLayout = new QHBoxLayout(content);
    content->setLayout(contentLayout);
    mainLayout->addWidget(content);

    // Graph
    QWidget* graphBox = new QWidget(content);
    QLayout* graphBoxLayout = new QVBoxLayout(graphBox);
    graphBox->setLayout(graphBoxLayout);
    graphBoxLayout->setAlignment(Qt::AlignHCenter);
    contentLayout->addWidget(graphBox);

    // Point x Time graph
    QChartView* plot = new QChartView(graphBox);
    plot->setRenderHint(QPainter::Antialiasing);
    graphBoxLayout->addWidget(plot);
    QChart* chart = new QChart;
    plot->setChart(chart);
    chart->setTitle("Temps en fonction de l'atteinte d'une cible n");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries* expSeries = new QLineSeries(chart);
    expSeries->setName("Courbe expérimental");
    QLineSeries* fittsSeries = new QLineSeries(chart);
    fittsSeries->setName("Courbe théorique");
    QCategoryAxis* axis = new QCategoryAxis(chart);

    std::list<qint64>::const_iterator time = stats.times.begin();
    std::list<qint64>::const_iterator fittsTime = stats.fittsTimes.begin();
    std::list<double>::const_iterator distance = stats.distances.begin();
    std::list<double>::const_iterator size = stats.sizes.begin();
    for (std::size_t i = 0; i < config.nbPoint; ++i) {
        expSeries->append(i, *time);
        fittsSeries->append(i, *fittsTime);

        axis->append(QString::number(i+1) + "<br/>T: " + QString::number(*time) + "<br/>D: " + QString::number(*distance, 'f', 3), i);

        ++time;
        ++distance;
        ++size;
        ++fittsTime;
    }
    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addSeries(expSeries);
    chart->addSeries(fittsSeries);

    chart->setAxisX(axis, expSeries);
    chart->setAxisX(axis, fittsSeries);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText("Temps (en ms)");
    chart->setAxisY(axisY, expSeries);

    // Distance relative x time.
    // Il faut ordonné les distances relative.
    // 1. On fait une copie de chaque liste
    std::list<qint64> unorderedTimes = stats.times;
    std::list<double> unorderedDistances = stats.distances;
    std::list<double> unorderedSizes = stats.sizes;
    std::list<qint64> orderedTimes;
    std::list<double> orderedRelativeDistance;

    // 2. Tant qu'une des listes n'est pas vide
    while (!unorderedDistances.empty()) {
        // 2.a on défini les minimum comme étant le premier élément de chaque liste.
        std::list<qint64>::const_iterator lessTime = unorderedTimes.begin();
        std::list<double>::const_iterator lessDistance = unorderedDistances.begin();
        std::list<double>::const_iterator lessSize = unorderedSizes.begin();

        // 2.b On défini la distance relative du premier élément.
        double D = *lessDistance;
        double L = *lessSize;
        double lessRelativeD = log(2*D / L);

        // 2.c On défini des itérateurs qui parcoureront chacune des listes
        time = lessTime;
        distance = lessDistance;
        size = lessSize;
        // 2.d On parcours les listes à la recherche de la plus petite distance relative
        for (std::size_t i = 0; i < unorderedDistances.size(); ++i) {
            D = *distance;
            L = *size;

            double relativeD;
            if (D == 0) relativeD = 0;
            else relativeD = log(2*D / L);

            if (relativeD < lessRelativeD) {
                lessRelativeD = relativeD;
                lessTime = time;
                lessDistance = distance;
                lessSize = size;
            }

            ++distance;
            ++size;
            ++time;
        }

        // 3. On ajoute la plus petite distance relative à nos liste ordonnées
        orderedRelativeDistance.push_back(lessRelativeD);
        orderedTimes.push_back(*lessTime);

        // 4. On supprime les éléments ajouté de nos liste originales.
        unorderedTimes.erase(lessTime);
        unorderedDistances.erase(lessDistance);
        unorderedSizes.erase(lessSize);
    }

    // On dessine le graph
    plot = new QChartView(graphBox);
    plot->setRenderHint(QPainter::Antialiasing);
    graphBoxLayout->addWidget(plot);
    chart = new QChart;
    plot->setChart(chart);
    chart->setTitle("Temps en fonction de la distance relative");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setAlignment(Qt::AlignBottom);

    expSeries = new QLineSeries(chart);
    axis = new QCategoryAxis(chart);

    time = orderedTimes.begin();
    distance = orderedRelativeDistance.begin();
    for (std::size_t i = 0; i < config.nbPoint; ++i) {
        expSeries->append(*distance, *time);

        axis->append("T: " + QString::number(*time, 'f', 3) + "<br/>D: " + QString::number(*distance, 'f', 3), i);

        ++time;
        ++distance;
    }
    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addSeries(expSeries);

    chart->setAxisX(axis, expSeries);

    axisY = new QValueAxis;
    axisY->setTitleText("Temps (en ms)");
    chart->setAxisY(axisY, expSeries);

    // Statistiques
    QWidget* statBox = new QWidget(content);
    QLayout* statLayout = new QVBoxLayout(statBox);
    statBox->setLayout(statLayout);
    statLayout->setAlignment(Qt::AlignHCenter);
    contentLayout->addWidget(statBox);

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

    QLabel* tailleIntervalleLabel = new QLabel("Intervalle de taille des cibles (mm) : " + QString::number(config.maxSize - config.minSize), parametreBox);
    parametreLayout->addWidget(tailleIntervalleLabel);


    // Résultats du test
    QGroupBox* resultatBox = new QGroupBox("Résultats de l'expérience");
    statLayout->addWidget(resultatBox);

    QLayout* resultatLayout = new QVBoxLayout();
    resultatBox->setLayout(resultatLayout);

    QLabel* ecartTypeLabel = new QLabel("Ecart-Type : " + QString::number(stats.ecartType, 'f', 3), resultatBox);
    resultatLayout->addWidget(ecartTypeLabel);

    QLabel* erreurTypeLabel = new QLabel("Erreur-Type : " + QString::number(stats.erreurType, 'f', 3), resultatBox);
    resultatLayout->addWidget(erreurTypeLabel);

    QLabel* differenceLabel = new QLabel("Différence moyenne : " + QString::number(stats.diffMoy, 'f', 3), resultatBox);
    resultatLayout->addWidget(differenceLabel);

    QLabel* intervalleLabel = new QLabel("Intervalle de confiance à 95% : " + QString::number(stats.itc95, 'f', 3), resultatBox);
    resultatLayout->addWidget(intervalleLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout(this);
    mainLayout->addItem(btnLayout);

    QPushButton* leaveBtn = new QPushButton("Quitter", this);
    btnLayout->addWidget(leaveBtn);

    QPushButton* restartBtn = new QPushButton("Recommencer", this);
    btnLayout->addWidget(restartBtn);

    connect(leaveBtn, SIGNAL(clicked()), this, SLOT(quitButtonHandler()));
    connect(restartBtn, SIGNAL(clicked()), this, SLOT(restartButtonHandler()));
}

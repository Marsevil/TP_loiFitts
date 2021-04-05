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
    graphBox->setLayout(graphBoxLayout);
    graphBoxLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(graphBox);

    QChartView* plot = new QChartView(graphBox);
    plot->setRenderHint(QPainter::Antialiasing);
    graphBoxLayout->addWidget(plot);
    QChart* chart = new QChart;
    plot->setChart(chart);
    chart->setTitle("Résultat loi Fitts");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QLineSeries* expSeries = new QLineSeries(chart);
    expSeries->setName("Courbe expérimental");
    QLineSeries* fittsSeries = new QLineSeries(chart);
    fittsSeries->setName("Courbe théorique");
    QCategoryAxis* axis = new QCategoryAxis(chart);

    std::list<double>::const_iterator time = stats.times.begin();
    std::list<double>::const_iterator distance = stats.distances.begin();
    std::list<double>::const_iterator size = stats.sizes.begin();
    for (std::size_t i = 0; i < config.nbPoint; ++i) {
        expSeries->append(i, *time);

        double D = *distance;
        double W = *size;
        double value = (config.a * 1000) + ((config.b * 1000) * log2((D / W) + 1));
        fittsSeries->append(i, value);

        axis->append(QString::number(i+1) + "<br/>T: " + QString::number(*time) + "<br/>D: " + QString::number(*distance), i);

        ++time;
        ++distance;
        ++size;
    }
    axis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addSeries(expSeries);
    chart->addSeries(fittsSeries);

    chart->setAxisX(axis, expSeries);
    chart->setAxisX(axis, fittsSeries);

    QValueAxis* axisY = new QValueAxis;
    axisY->setTitleText("temps (en ms)");
    chart->setAxisY(axisY, expSeries);

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

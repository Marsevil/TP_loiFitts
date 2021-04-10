#include "configview.h"

ConfigView::ConfigView(Config _config, QWidget *parent)
    : QWidget(parent), config(_config)
{
    QLayout* mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    //QWidget* centeredWidget = new QWidget;
    //centeredWidget->setMaximumWidth(800);
    QLayout* centeredLayout = new QVBoxLayout;
    //centeredLayout->addWidget(centeredWidget);
    centeredLayout->setAlignment(Qt::AlignHCenter);

    //mainLayout->addWidget(centeredWidget);
    mainLayout->addItem(centeredLayout);


    // Titre
    QWidget* titleBox = new QWidget(this);
    QLayout* titleBoxLayout = new QVBoxLayout(titleBox);
    titleBox->setLayout(titleBoxLayout);
    titleBoxLayout->setAlignment(Qt::AlignHCenter);
    QLabel* title = new QLabel("Rappel de la formule", this);
    QFont titleFont("Calibri", 20, QFont::Bold);
    title->setFont(titleFont);
    titleBoxLayout->addWidget(title);

    centeredLayout->addWidget(titleBox);


    // Formule
    QWidget* formulaBox = new QWidget(this);
    QLayout* formulaBoxLayout = new QVBoxLayout(formulaBox);
    formulaBoxLayout->setAlignment(Qt::AlignHCenter);
    formulaBox->setLayout(formulaBoxLayout);
    QSvgWidget* formula = new QSvgWidget("./fittsFormula.svg", formulaBox);
    formulaBoxLayout->addWidget(formula);

    centeredLayout->addWidget(formulaBox);

    QFont font("Calibri", 15, QFont::Bold);

    // Menu utilisateur
    QWidget* userSide = new QWidget(this);
    QLayout* userSideLayout = new QHBoxLayout(userSide);
    userSide->setLayout(userSideLayout);

    centeredLayout->addWidget(userSide);

    // Paramètre de la formule
    QGroupBox* formulaSettings = new QGroupBox("Paramètre de la formule :", this);
    QLayout* formulaSettingsLayout = new QVBoxLayout(formulaSettings);
    formulaSettings->setLayout(formulaSettingsLayout);
    userSideLayout->addWidget(formulaSettings);

    // Box pour le choix de a et de b
    QWidget* abSettings = new QWidget(formulaSettings);
    QLayout* abSettingsLayout = new QHBoxLayout(abSettings);
    abSettings->setLayout(abSettingsLayout);
    formulaSettingsLayout->addWidget(abSettings);

    // Choix de a
    QWidget* aSettings = new QWidget(abSettings);
    QLayout* aSettingsLayout = new QHBoxLayout(aSettings);
    QLabel* aLabel = new QLabel("a = ", aSettings);
    aLabel->setFont(font);
    QDoubleSpinBox* aSelector = new QDoubleSpinBox(aSettings);
    aSelector->setValue(config.a);
    aSettings->setLayout(aSettingsLayout);
    aSettingsLayout->addWidget(aLabel);
    aSettingsLayout->addWidget(aSelector);
    abSettingsLayout->addWidget(aSettings);

    // Choix de b
    QWidget* bSettings = new QWidget(abSettings);
    QLayout* bSettingsLayout = new QHBoxLayout(bSettings);
    QLabel* bLabel = new QLabel("b = ", bSettings);
    bLabel->setFont(font);
    QDoubleSpinBox* bSelector = new QDoubleSpinBox(bSettings);
    bSelector->setValue(config.b);
    bSettings->setLayout(bSettingsLayout);
    bSettingsLayout->addWidget(bLabel);
    bSettingsLayout->addWidget(bSelector);
    abSettingsLayout->addWidget(bSettings);

    // C'est quoi les variables
    QWidget* variablesExplanation = new QWidget(formulaSettings);
    QLayout* variablesExplanationLayout = new QHBoxLayout(variablesExplanation);
    variablesExplanation->setLayout(variablesExplanationLayout);
    QLabel* with = new QLabel("Rappel : ", variablesExplanation);
    with->setFont(font);
    QLabel* explanation = new QLabel("D la distance \nW la taille de la cible");
    explanation->setFont(font);
    variablesExplanationLayout->addWidget(with);
    variablesExplanationLayout->addWidget(explanation);
    formulaSettingsLayout->addWidget(variablesExplanation);

    // Paramètre du test
    QGroupBox* testSettings = new QGroupBox("Paramètre du test :", this);
    QLayout* testSettingsLayout = new QVBoxLayout(testSettings);
    testSettings->setLayout(testSettingsLayout);
    userSideLayout->addWidget(testSettings);

    // Nombre de cible
    QWidget* nbTargets = new QWidget(testSettings);
    QLayout* nbTargetsLayout = new QHBoxLayout(nbTargets);
    QLabel* nbTargetsLabel = new QLabel("Nombre de cible :", nbTargets);
    QSpinBox* nbTargetsSelector = new QSpinBox(nbTargets);
    nbTargetsSelector->setMinimum(0);
    nbTargetsSelector->setValue(config.nbPoint);
    nbTargetsLayout->addWidget(nbTargetsLabel);
    nbTargetsLayout->addWidget(nbTargetsSelector);
    testSettingsLayout->addWidget(nbTargets);

    // Taille minimale de la cible
    QWidget* minimumSize = new QWidget(testSettings);
    QLayout* minimumSizeLayout = new QHBoxLayout(minimumSize);
    QLabel* minimumSizeLabel = new QLabel("Taille minimum de la cible (mm) :", minimumSize);
    QSpinBox* minimumSizeSelector = new QSpinBox(minimumSize);
    minimumSizeSelector->setMinimum(0);
    minimumSizeSelector->setMaximum(MAX_MIN_RANGE);
    minimumSizeSelector->setValue(config.minSize);
    minimumSizeLayout->addWidget(minimumSizeLabel);
    minimumSizeLayout->addWidget(minimumSizeSelector);
    testSettingsLayout->addWidget(minimumSize);

    // Taille maximale de la cible
    QWidget* maximumSize = new QWidget(testSettings);
    QLayout* maximumSizeLayout = new QHBoxLayout(maximumSize);
    QLabel* maximumSizeLabel = new QLabel("Taille minimum de la cible (mm) :", maximumSize);
    QSpinBox* maximumSizeSelector = new QSpinBox(maximumSize);
    maximumSizeSelector->setMaximum(MAX_MIN_RANGE);
    maximumSizeSelector->setMinimum(0);
    maximumSizeSelector->setValue(config.maxSize);
    maximumSizeLayout->addWidget(maximumSizeLabel);
    maximumSizeLayout->addWidget(maximumSizeSelector);
    testSettingsLayout->addWidget(maximumSize);

    // Boutons
    QWidget* buttons = new QWidget(this);
    centeredLayout->addWidget(buttons);

    QLayout* buttonsLayout = new QHBoxLayout(buttons);
    buttons->setLayout(buttonsLayout);
    QPushButton* cancel = new QPushButton("Annuler", buttons);
    buttonsLayout->addWidget(cancel);
    QPushButton* confirm = new QPushButton("Valider", buttons);
    buttonsLayout->addWidget(confirm);

    connect(aSelector, SIGNAL(valueChanged(double)), this, SLOT(updateA(double)));
    connect(bSelector, SIGNAL(valueChanged(double)), this, SLOT(updateB(double)));
    connect(nbTargetsSelector, SIGNAL(valueChanged(int)), this, SLOT(updateNbPoint(int)));
    connect(maximumSizeSelector, SIGNAL(valueChanged(int)), this, SLOT(updateMaxSize(int)));
    connect(minimumSizeSelector, SIGNAL(valueChanged(int)), this, SLOT(updateMinSize(int)));

    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));
    connect(confirm, SIGNAL(clicked()), this, SLOT(confirmPressed()));

}

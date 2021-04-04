#include "configview.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QSvgWidget>
#include <QPushButton>

ConfigView::ConfigView(QWidget *parent) : QWidget(parent)
{
    QLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Titre
    QWidget* titleBox = new QWidget(this);
    QLayout* titleBoxLayout = new QVBoxLayout(titleBox);
    titleBox->setLayout(titleBoxLayout);
    titleBoxLayout->setAlignment(Qt::AlignHCenter);
    QLabel* title = new QLabel("Rappel de la formule", this);
    QFont titleFont("Calibri", 20, QFont::Bold);
    title->setFont(titleFont);
    titleBoxLayout->addWidget(title);
    mainLayout->addWidget(titleBox);

    // Formule
    QWidget* formulaBox = new QWidget(this);
    QLayout* formulaBoxLayout = new QVBoxLayout(formulaBox);
    formulaBoxLayout->setAlignment(Qt::AlignHCenter);
    formulaBox->setLayout(formulaBoxLayout);
    QSvgWidget* formula = new QSvgWidget("./fittsFormula.svg", formulaBox);
    formulaBoxLayout->addWidget(formula);
    mainLayout->addWidget(formulaBox);

    QFont font("Calibri", 15, QFont::Bold);

    // Menu utilisateur
    QWidget* userSide = new QWidget(this);
    QLayout* userSideLayout = new QHBoxLayout(userSide);
    userSide->setLayout(userSideLayout);
    mainLayout->addWidget(userSide);

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
    QSpinBox* aSelector = new QSpinBox(aSettings);
    aSettings->setLayout(aSettingsLayout);
    aSettingsLayout->addWidget(aLabel);
    aSettingsLayout->addWidget(aSelector);
    abSettingsLayout->addWidget(aSettings);

    // Choix de b
    QWidget* bSettings = new QWidget(abSettings);
    QLayout* bSettingsLayout = new QHBoxLayout(bSettings);
    QLabel* bLabel = new QLabel("b = ", bSettings);
    bLabel->setFont(font);
    QSpinBox* bSelector = new QSpinBox(bSettings);
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
    nbTargetsLayout->addWidget(nbTargetsLabel);
    nbTargetsLayout->addWidget(nbTargetsSelector);
    testSettingsLayout->addWidget(nbTargets);

    // Taille minimal de la cible
    QWidget* minimumSize = new QWidget(testSettings);
    QLayout* minimumSizeLayout = new QHBoxLayout(minimumSize);
    QLabel* minimumSizeLabel = new QLabel("Taille minimum de la cible :", minimumSize);
    QSpinBox* minimumSizeSelector = new QSpinBox(minimumSize);
    minimumSizeLayout->addWidget(minimumSizeLabel);
    minimumSizeLayout->addWidget(minimumSizeSelector);
    testSettingsLayout->addWidget(minimumSize);

    // Taille maximal de la cible
    QWidget* maximumSize = new QWidget(testSettings);
    QLayout* maximumSizeLayout = new QHBoxLayout(maximumSize);
    QLabel* maximumSizeLabel = new QLabel("Taille minimum de la cible :", maximumSize);
    QSpinBox* maximumSizeSelector = new QSpinBox(maximumSize);
    maximumSizeLayout->addWidget(maximumSizeLabel);
    maximumSizeLayout->addWidget(maximumSizeSelector);
    testSettingsLayout->addWidget(maximumSize);

    // Boutons
    QWidget* buttons = new QWidget(this);
    mainLayout->addWidget(buttons);
    QLayout* buttonsLayout = new QHBoxLayout(buttons);
    buttons->setLayout(buttonsLayout);
    QPushButton* cancel = new QPushButton("Annuler", buttons);
    buttonsLayout->addWidget(cancel);
    QPushButton* confirm = new QPushButton("Valider", buttons);
    buttonsLayout->addWidget(confirm);
}

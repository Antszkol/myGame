#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QApplication>
#include "menuWidget.hpp"
#include "settingsWidget.hpp"

menuWidget::menuWidget(setting* settingsPtr){
    this->settingsPtr = settingsPtr;

    QFont font("Garamond", 16);
    this->setFont(font);

    QPushButton* battleButton = new QPushButton("Battle!", this);
    QPushButton* settingsButton = new QPushButton("Settings", this);
    QPushButton* exitButton = new QPushButton("Exit", this);

    connect(battleButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::battle);});
    connect(settingsButton, &QPushButton::clicked, this, [this](){
        settingsWidget* dialog = new settingsWidget(this->settingsPtr, this);
        dialog->exec();
    });
    connect(exitButton, &QPushButton::clicked, this, [this](){
        qApp->quit();
    });

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(battleButton);
    layout->addWidget(settingsButton);
    layout->addWidget(exitButton);
}

menuWidget::~menuWidget(){}
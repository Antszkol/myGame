#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>
#include <QApplication>
#include "menuWidget.hpp"
#include "settingsWidget.hpp"

MenuWidget::MenuWidget(Setting* settingsPtr){
    this->settingsPtr_ = settingsPtr;

    QFont font("Garamond", 16);
    this->setFont(font);

    QPushButton* battleButton = new QPushButton("Battle!", this);
    QPushButton* settingsButton = new QPushButton("Settings", this);
    QPushButton* exitButton = new QPushButton("Exit", this);

    connect(battleButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::battleMenuWidget);});
    connect(settingsButton, &QPushButton::clicked, this, [this](){
        SettingsWidget* dialog = new SettingsWidget(this->settingsPtr_, this);
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

MenuWidget::~MenuWidget(){}
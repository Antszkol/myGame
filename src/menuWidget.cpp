#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QApplication>
#include "menuWidget.hpp"
#include "settingsWidget.hpp"

MenuWidget::MenuWidget(Setting* settingsPtr){
    this->settingsPtr_ = settingsPtr;
    this->setAttribute(Qt::WA_StyledBackground, true);

    QPushButton* battleButton = new QPushButton("Battle!", this);
    battleButton->setStyleSheet("font-size: 24pt;");
    QPushButton* settingsButton = new QPushButton("Settings", this);
    settingsButton->setStyleSheet("font-size: 24pt;");
    QPushButton* exitButton = new QPushButton("Exit", this);
    exitButton->setStyleSheet("font-size: 24pt;");

    connect(battleButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::battleMenuWidget);});
    connect(settingsButton, &QPushButton::clicked, this, [this](){
        SettingsWidget* dialog = new SettingsWidget(this->settingsPtr_, this);
        dialog->exec();
    });
    connect(exitButton, &QPushButton::clicked, this, [this](){
        qApp->quit();
    });

    QVBoxLayout* layout = new QVBoxLayout(this);
    for(QPushButton* button : {battleButton, settingsButton, exitButton}){
        QHBoxLayout* buttonRowLayout = new QHBoxLayout();
        buttonRowLayout->addStretch(1);
        buttonRowLayout->addWidget(button, 1);
        buttonRowLayout->addStretch(1);
        layout->addLayout(buttonRowLayout);
    }
}

MenuWidget::~MenuWidget(){}
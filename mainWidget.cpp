#include "mainWidget.hpp"

void mainWidget::switchScreen(Screen target){
    switch(target){
        case Screen::menu:
            stack->setCurrentIndex(target);
            break;
        case Screen::battle:
            stack->setCurrentIndex(target);
            break;
    }
}

mainWidget::mainWidget(QWidget *parent){
    settingsPtr = new setting();
    battleSettingPtr = new battleSetting();

    setWindowFlags(Qt::FramelessWindowHint);
    pair<int,int> startupSize = settingsPtr->getWindowSize();
    setFixedSize(startupSize.first, startupSize.second);

    menuWidget* menu = new menuWidget(settingsPtr);
    battleWidget* battle = new battleWidget(battleSettingPtr);

    QVBoxLayout* layout = new QVBoxLayout(this);
    stack = new QStackedWidget(this);

    layout->addWidget(stack);

    connect(menu, &baseScreenWidget::screenChanged, this, &mainWidget::switchScreen);
    connect(battle, &baseScreenWidget::screenChanged, this, &mainWidget::switchScreen);

    stack->addWidget(menu);
    stack->addWidget(battle);
}

mainWidget::~mainWidget(){}
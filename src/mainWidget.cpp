#include "mainWidget.hpp"

void MainWidget::switchScreen(Screen target){
    switch(target){
        case Screen::menuWidget:
            stack_->setCurrentIndex(target);
            break;
        case Screen::battleWidget:
            stack_->setCurrentIndex(target);
            break;
        case Screen::battleMenuWidget:
            stack_->setCurrentIndex(target);
            break;
    }
}

MainWidget::MainWidget(QWidget *parent){
    settingsPtr_ = new Setting();
    battleSettingPtr_ = new BattleSetting();
    battlePtr_ = nullptr; // created once a battle actually starts

    setWindowFlags(Qt::FramelessWindowHint);
    pair<int,int> startupSize = settingsPtr_->getWindowSize();
    setFixedSize(startupSize.first, startupSize.second);

    MenuWidget* menuWidget = new MenuWidget(settingsPtr_);
    BattleWidget* battleWidget = new BattleWidget();
    BattleMenuWidget* battleMenuWidget = new BattleMenuWidget(battleSettingPtr_);

    QVBoxLayout* layout = new QVBoxLayout(this);
    stack_ = new QStackedWidget(this);

    layout->addWidget(stack_);

    connect(menuWidget, &BaseScreenWidget::screenChanged, this, &MainWidget::switchScreen);
    connect(battleWidget, &BaseScreenWidget::screenChanged, this, &MainWidget::switchScreen);
    connect(battleMenuWidget, &BaseScreenWidget::screenChanged, this, &MainWidget::switchScreen);
    connect(battleMenuWidget, &BattleMenuWidget::battleCreated, battleWidget, &BattleWidget::setBattle);

    stack_->addWidget(menuWidget);
    stack_->addWidget(battleWidget);
    stack_->addWidget(battleMenuWidget);
}

MainWidget::~MainWidget(){}
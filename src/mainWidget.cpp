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

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet(
        "QWidget {"
        "   background-color: #141414;"
        "   color: #eaeaea;"
        "   font-family: \"EB Garamond\";"
        "   font-size: 20pt;"
        "   font-weight: 63;"
        "   font-style: italic;"
        "}"
        "QPushButton {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #858585, stop:1 #353535);"
        "   border: 1px solid #888888;"
        "   border-radius: 8px;"
        "   padding: 8px 12px;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8e8e8, stop:1 #b8b8b8);"
        "}"
        "QPushButton:pressed { background-color: #909090; }"
    );

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
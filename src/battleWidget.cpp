#pragma once
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mapWidget.hpp"
#include "baseScreenWidget.hpp"
#include "battleWidget.hpp"
#include "resultWidget.hpp"

BattleWidget::BattleWidget(){
    QFont font("Garamond", 16);
    this->setFont(font);
    
    this->layout_ = new QHBoxLayout(this);
    this->setShopWidget();
    this->setActionWidget();

    QPushButton* quitBattleButton = new QPushButton("Quit battle", actionWidgetPtr_);
    connect(quitBattleButton, &QPushButton::clicked, this, [this](){
        MapWidget* deleteMapWidgetPtr = this->mapWidgetPtr_;
        delete deleteMapWidgetPtr;
        this->mapWidgetPtr_ = nullptr;
        navigateTo(Screen::menuWidget);});
    this->actionWidgetPtr_->layout_->addWidget(quitBattleButton);
}

BattleWidget::~BattleWidget(){
    MapWidget* deleteMapWidgetPtr = this->mapWidgetPtr_;
    delete deleteMapWidgetPtr;
}

void BattleWidget::battleEnded(const Player* winnerPtr){
    Player* player1Ptr = this->turnHandlerPtr_->getPlayerPtr(1);
    Player* player2Ptr = this->turnHandlerPtr_->getPlayerPtr(2);

    std::vector<Message*> messagePtrVector;
    for(const auto& messagePtr : this->turnHandlerPtr_->getLoggerPtr()->getMessages()){
        messagePtrVector.push_back(messagePtr.get());
    }

    ResultWidget resultWidget(winnerPtr->getPlayerIdx(), player1Ptr->getPlayerStats(), player2Ptr->getPlayerStats(), messagePtrVector, this);
    resultWidget.exec();
    this->navigateTo(Screen::menuWidget);
}


void BattleWidget::setShopWidget(){
    shopWidgetPtr_ = new ShopWidget();
    layout_->insertWidget(0, shopWidgetPtr_, 1);
    return;
}

void BattleWidget::setActionWidget(){
    actionWidgetPtr_ = new ActionWidget();
    layout_->insertWidget(0, actionWidgetPtr_, 1);
    return;
}

void BattleWidget::setBattle(Battle* battlePtr, BattleSetting* battleSettingPtr){
    battleSettingPtr_ = battleSettingPtr;
    battlePtr_ = battlePtr;
    int lastColumn = battlePtr_->getMap()->getMapSize().first - 1;
    turnHandlerPtr_ = std::make_unique<TurnHandler>(this, this->shopWidgetPtr_, this->actionWidgetPtr_, lastColumn);
    connect(this->turnHandlerPtr_.get(), &TurnHandler::battleEnded, this, &BattleWidget::battleEnded);
    this->actionWidgetPtr_->setCurrentPlayerStats(this->turnHandlerPtr_->getPlayerPtr(1));
    if(this->mapWidgetPtr_ == nullptr){
        mapWidgetPtr_ = new MapWidget(*battlePtr->getMap(), this->turnHandlerPtr_.get());
    }
    layout_->insertWidget(1, mapWidgetPtr_, 3);
    return;
}

MapWidget* BattleWidget::getMapWidgetPtr(){
    return this->mapWidgetPtr_;
}
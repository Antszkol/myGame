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

BattleWidget::BattleWidget(){
    QFont font("Garamond", 16);
    this->setFont(font);
    
    this->layout_ = new QHBoxLayout(this);
    this->setShopWidget();
    this->setActionWidget();

    QPushButton* backButton = new QPushButton("Back", actionWidgetPtr_);
    connect(backButton, &QPushButton::clicked, this, [this](){
        MapWidget* deleteMapWidgetPtr = this->mapWidgetPtr_;
        delete deleteMapWidgetPtr;
        this->mapWidgetPtr_ = nullptr;
        navigateTo(Screen::menuWidget);});
    this->actionWidgetPtr_->layout_->addWidget(backButton);
}

BattleWidget::~BattleWidget(){
    MapWidget* deleteMapWidgetPtr = this->mapWidgetPtr_;
    delete deleteMapWidgetPtr;
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
    this->actionWidgetPtr_->setCurrentPlayerStats(this->turnHandlerPtr_->getPlayerPtr(1));
    if(this->mapWidgetPtr_ == nullptr){
        mapWidgetPtr_ = new MapWidget(*battlePtr->getMap(), this->turnHandlerPtr_.get());
    }
    layout_->insertWidget(1, mapWidgetPtr_, 3);
    return;
}

//problem:
//
//BattleWidget::setBattle() tworzy nowy TurnHandler i MapWidget
//trzeba usunac manualnie MapWidget
//i unique_ptr dac na TurnHandler


MapWidget* BattleWidget::getMapWidgetPtr(){
    return this->mapWidgetPtr_;
}
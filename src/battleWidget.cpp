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

    QFrame* hudPanel = new QFrame(this);
    hudPanel->setFrameShape(QFrame::Box);
    QVBoxLayout* hudLayout = new QVBoxLayout(hudPanel);

    this->goldLabel_ = new QLabel("Gold: -", hudPanel);
    hudLayout->addWidget(goldLabel_);

    QPushButton* backButton = new QPushButton("Back", hudPanel);
    connect(backButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::menuWidget);});
    hudLayout->addWidget(backButton);

    this->layout_ = new QHBoxLayout(this);
    this->setShop();
    this->turnHandlerPtr_ = new TurnHandler(this, this->shopWidgetPtr_);

    layout_->addWidget(hudPanel, 1);
}

BattleWidget::~BattleWidget(){}

void BattleWidget::setShop(){
    shopWidgetPtr_ = new ShopWidget();
    layout_->insertWidget(0, shopWidgetPtr_, 1);
    return;
}

MapWidget* BattleWidget::getMapWidgetPtr(){
    return this->mapWidgetPtr_;
}

void BattleWidget::setBattle(Battle* battlePtr, BattleSetting* battleSettingPtr){
    battleSettingPtr_ = battleSettingPtr;
    battlePtr_ = battlePtr;
    mapWidgetPtr_ = new MapWidget(*battlePtr->getMap(), this->turnHandlerPtr_);
    layout_->insertWidget(1, mapWidgetPtr_, 3);
    return;
}
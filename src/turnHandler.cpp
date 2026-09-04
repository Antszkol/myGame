#pragma once
#include "turnHandler.hpp"
#include "battleWidget.hpp"
#include "shopWidget.hpp"

TurnHandler::TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr, int lastMapColumn){
    Player* player1 = new Player(1, 0);
    Player* player2 = new Player(2, lastMapColumn); 
    this->actionMode_ = ActionMode::None;
    this->players_ = {player1, player2};

    this->currentPlayerPtr_ = this->players_.first;
    this->battleWidgetPtr_ = battleWidgetPtr;
    this->shopWidgetPtr_ = shopWidgetPtr;
    this->actionWidgetPtr_ = actionWidgetPtr;

    this->turnNumber_ = 0;
    this->isTurnFinished_ = false;

    connect(this->shopWidgetPtr_, &ShopWidget::unitPurchaseRequested, this, [this](UnitType unitType){
            this->recruitUnitSlot(unitType);});

    connect(this->actionWidgetPtr_, &ActionWidget::endTurnRequested, this, [this](){
            this->switchPlayerSlot();});
    
    connect(this->actionWidgetPtr_, &ActionWidget::moveUnitRequested, [this](){
            this->moveUnitSlot();});
    
    connect(this->actionWidgetPtr_, &ActionWidget::attackUnitRequested, [this](){
            this->attackUnitSlot();});
};

Player* TurnHandler::getPlayerPtr(int playerIdx){
    return playerIdx == 1 ? players_.first : players_.second;
}

void TurnHandler::moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest){
    Unit* unitPtr = tileWidgetStart->getTilePtr()->getOccupant();
    unitPtr->getUnitWidgetPtr()->setCurrentTileWidget(tileWidgetDest);
    tileWidgetStart->getTilePtr()->setOccupation(nullptr);
    tileWidgetDest->getTilePtr()->setOccupation(unitPtr);
    
    return;
}

void TurnHandler::attackUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest){
    Unit* unitPtr = tileWidgetStart->getTilePtr()->getOccupant();
    int damage = unitPtr->getUnitStats().damage_;

    if(damage < tileWidgetDest->getTilePtr()->getOccupant()->getRemainingHealth()){
        tileWidgetDest->getTilePtr()->getOccupant()->dealDamage(damage);
    }
    else if(true){
        Unit* deleteUnitPtr = tileWidgetDest->getTilePtr()->getOccupant();
        UnitWidget* deleteUnitWidgetPtr = deleteUnitPtr->getUnitWidgetPtr();

        tileWidgetDest->getTilePtr()->setOccupation(nullptr);

        delete deleteUnitPtr;
        delete deleteUnitWidgetPtr;

        return;
    }
    return;
}

void TurnHandler::switchPlayer(){
    if(currentPlayerPtr_ == players_.first){
        currentPlayerPtr_ = players_.second;
        this->actionWidgetPtr_->setCurrentPlayerStats(players_.second);
    }
    else if(currentPlayerPtr_ == players_.second){
        currentPlayerPtr_ = players_.first;
        this->actionWidgetPtr_->setCurrentPlayerStats(players_.first);
    }
    this->currentPlayerPtr_->refreshUnitsSpeed();
    return;
}

void TurnHandler::setActionMode(ActionMode actionMode){
    this->actionMode_ = actionMode;
    return;
}

void TurnHandler::moveUnitSlot(){
    this->actionMode_ = ActionMode::MoveUnit;
}

void TurnHandler::attackUnitSlot(){
    this->actionMode_ = ActionMode::AttackUnit;
}

void TurnHandler::recruitUnitSlot(UnitType unitTypeIdx){
    if(currentPlayerPtr_->getGold() >= 50){
        this->shopWidgetPtr_->buyUnit(currentPlayerPtr_, unitTypeIdx);
        this->pendingUnitType_ = unitTypeIdx;
        this->actionMode_ = ActionMode::RecruitUnit;
    }
}

ActionWidget* TurnHandler::getActionWidgetPtr(){
    return this->actionWidgetPtr_;
}

void TurnHandler::switchPlayerSlot(){
    this->switchPlayer();
    return;
}

Player* TurnHandler::getCurrentPlayerPtr(){
    return this->currentPlayerPtr_;
}

void TurnHandler::confirmUnitDeployment(TileWidget* tileWidgetPtr){
    if(this->actionMode_ == ActionMode::RecruitUnit){
        UnitWidget* unitWidgetPtr = new UnitWidget(this->pendingUnitType_, tileWidgetPtr);
        Unit* unitPtr = new Unit(this->currentPlayerPtr_, this->pendingUnitType_, UnitStatsMap.at(this->pendingUnitType_), unitWidgetPtr);
        unitWidgetPtr->setUnitPtr(unitPtr);
        tileWidgetPtr->getTilePtr()->setOccupation(unitWidgetPtr->getUnitPtr());
        this->currentPlayerPtr_->addUnit(unitPtr);
        this->actionMode_ = ActionMode::None;
        this->getActionWidgetPtr()->setCurrentPlayerStats(this->currentPlayerPtr_);
    }
    return;
}

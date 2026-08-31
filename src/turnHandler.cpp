#pragma once
#include "turnHandler.hpp"
#include "battleWidget.hpp"
#include "shopWidget.hpp"

TurnHandler::TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr){
    Player* player1 = new Player(1);
    Player* player2 = new Player(2); 
    this->actionMode_ = ActionMode::None;
    this->players_ = {player1, player2};

    this->currentPlayerPtr_ = this->players_.first;
    this->battleWidgetPtr_ = battleWidgetPtr;
    this->shopWidgetPtr_ = shopWidgetPtr;
    this->actionWidgetPtr_ = actionWidgetPtr;

    this->turnNumber_ = 0;
    this->isTurnFinished_ = false;

    connect(this->shopWidgetPtr_, &ShopWidget::unitPurchaseRequested, this, [this](UnitType unitType){
            this->recruitUnitSlot(this->currentPlayerPtr_, unitType);});

    connect(this->actionWidgetPtr_, &ActionWidget::endTurnRequested, this, [this](){
            this->switchPlayerSlot();});
    
    connect(this->actionWidgetPtr_, &ActionWidget::moveUnitRequested, [this](){
            this->moveUnitSlot();});
};

Player* TurnHandler::getPlayerPtr(int playerIdx){
    if(playerIdx == 1){
        return this->players_.first;
    }
    else if(playerIdx == 2){
        return this->players_.second;
    }
}

void TurnHandler::moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest){
    Unit* unitPtr = tileWidgetStart->getTilePtr()->getOccupant();
    unitPtr->getUnitWidgetPtr()->setCurrentTileWidget(tileWidgetDest);
    tileWidgetStart->getTilePtr()->setOccupation(nullptr);
    tileWidgetDest->getTilePtr()->setOccupation(unitPtr);
    
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

void TurnHandler::recruitUnitSlot(Player* currentPlayerPtr, UnitType unitTypeIdx){
    if(currentPlayerPtr->getGold() >= 50){
        this->shopWidgetPtr_->buyUnit(currentPlayerPtr, unitTypeIdx);
        this->pendingUnitType_ = unitTypeIdx;
        //TileWidget* destinationTileWidgetPtr = this->battleWidgetPtr_->getMapWidgetPtr()->getTileWidgetPtr({0, 0});
        //UnitWidget* unitWidgetPtr = new UnitWidget(0, destinationTileWidgetPtr);
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

// Trzeba przeniesc stawianie jednostki z recruitUnit() do
// confirmUnitDeployment(), bo dopiero tam pobieramy
// odpowiedni TileWidget*.

void TurnHandler::confirmUnitDeployment(TileWidget* tileWidgetPtr){
    if(this->actionMode_ == ActionMode::RecruitUnit){
        UnitWidget* unitWidgetPtr = new UnitWidget(this->pendingUnitType_, tileWidgetPtr);
        Unit* unitPtr = new Unit(this->pendingUnitType_, UnitStatsMap.at(this->pendingUnitType_), unitWidgetPtr);
        unitWidgetPtr->setUnitPtr(unitPtr);
        tileWidgetPtr->getTilePtr()->setOccupation(unitWidgetPtr->getUnitPtr());
        this->currentPlayerPtr_->addUnit(unitPtr);
        this->actionMode_ = ActionMode::None;
        this->getActionWidgetPtr()->setCurrentPlayerStats(this->currentPlayerPtr_);
    }
}

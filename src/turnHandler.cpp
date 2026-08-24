#pragma once
#include "turnHandler.hpp"
#include "battleWidget.hpp"
#include "shopWidget.hpp"

TurnHandler::TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr){
    Player* player1 = new Player();
    Player* player2 = new Player(); 
    this->actionMode_ = ActionMode::None;
    this->players_ = {player1, player2};

    this->currentPlayer_ = this->players_.first;
    this->battleWidgetPtr_ = battleWidgetPtr;
    this->shopWidgetPtr_ = shopWidgetPtr;

    this->turnNumber_ = 0;
    this->isTurnFinished_ = false;

    connect(this->shopWidgetPtr_, &ShopWidget::unitPurchaseRequested, this, [this](UnitType unitType){
            this->recruitUnit(this->currentPlayer_, unitType);});
};

void TurnHandler::recruitUnit(Player* currentPlayerPtr, UnitType unitTypeIdx){
    if(currentPlayerPtr->getGold() >= 50){
        this->shopWidgetPtr_->buyUnit(currentPlayerPtr, unitTypeIdx);
        this->pendingUnitType_ = unitTypeIdx;
        //TileWidget* destinationTileWidgetPtr = this->battleWidgetPtr_->getMapWidgetPtr()->getTileWidgetPtr({0, 0});
        //UnitWidget* unitWidgetPtr = new UnitWidget(0, destinationTileWidgetPtr);
        this->actionMode_ = ActionMode::RecruitUnit;
    }
}

// Trzeba przeniesc stawianie jednostki z recruitUnit() do
// confirmUnitDeployment(), bo dopiero tam pobieramy
// odpowiedni TileWidget*.

void TurnHandler::confirmUnitDeployment(TileWidget* tileWidgetPtr){
    if(this->actionMode_ == ActionMode::RecruitUnit){
        UnitWidget* unitWidgetPtr = new UnitWidget(this->pendingUnitType_, tileWidgetPtr);
        tileWidgetPtr->getTilePtr()->setOccupation(true);
        this->actionMode_ = ActionMode::None;
    }
}

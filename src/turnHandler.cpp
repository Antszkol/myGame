#pragma once
#include "turnHandler.hpp"
#include "battleWidget.hpp"
#include "shopWidget.hpp"
#include <QTimer>
#include <random>
#include <memory>
#include "moveMessage.hpp"
#include "attackMessage.hpp"
#include "killMessage.hpp"
#include "recruitMessage.hpp"
#include "aiHandler.hpp"

TurnHandler::TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr, int lastMapColumn, bool isAI, BattleSetting* battleSettingPtr){
    Player* player1 = new Player(1, 0, false, battleSettingPtr->getStartGold());
    Player* player2 = nullptr;
    this->aiHandlerPtr_ = nullptr;

    if(isAI){
        player2 = new Player(2, lastMapColumn, true, battleSettingPtr->getStartGold());
    }
    else{
        player2 = new Player(2, lastMapColumn, false, battleSettingPtr->getStartGold());
    }

    this->actionMode_ = ActionMode::None;
    this->players_ = {player1, player2};

    this->currentPlayerPtr_ = this->players_.first;
    this->battleWidgetPtr_ = battleWidgetPtr;
    this->battleSettingPtr_ = battleSettingPtr;
    this->shopWidgetPtr_ = shopWidgetPtr;
    this->actionWidgetPtr_ = actionWidgetPtr;

    this->turnNumber_ = 0;
    this->isTurnFinished_ = false;

    connect(this->shopWidgetPtr_, &ShopWidget::unitPurchaseRequested, this, [this](UnitType unitType){
            this->recruitUnitSlot(unitType);});

    connect(this->actionWidgetPtr_, &ActionWidget::endTurnRequested, this, [this](){
            this->endTurnSlot();});

    connect(this->actionWidgetPtr_, &ActionWidget::moveUnitRequested, [this](){
            this->moveUnitSlot();});

    connect(this->actionWidgetPtr_, &ActionWidget::attackUnitRequested, [this](){
            this->attackUnitSlot();});
};

void TurnHandler::moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest){
    this->actionMode_ = ActionMode::None;
    Unit* unitPtr = tileWidgetStart->getTilePtr()->getOccupant();
    MapHandler* mapHandlerPtr = this->battleWidgetPtr_->getMapWidgetPtr()->getMapHandlerPtr();
    mapHandlerPtr->getUnitWidget(unitPtr)->setCurrentTileWidget(tileWidgetDest);
    tileWidgetStart->getTilePtr()->setOccupation(nullptr);
    tileWidgetDest->getTilePtr()->setOccupation(unitPtr);

    this->logger_.addMessage(std::make_unique<MoveMessage>(unitPtr->getOwnerPtr()->getPlayerIdx(), unitPtr->getUnitType(), tileWidgetStart->getTilePtr()->getTileIndex(), tileWidgetDest->getTilePtr()->getTileIndex()));
    this->actionWidgetPtr_->setLastMessage(this->logger_.getLastMessageText());

    if(tileWidgetDest->getTilePtr()->isWithinDeploymentZone(this->getNotCurrentPlayerPtr())){
        emit battleEnded(unitPtr->getOwnerPtr());
    }

    this->refreshUnitMorale();

    return;
}

void TurnHandler::attackUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest){
    this->actionMode_ = ActionMode::None;
    Unit* unitPtr = tileWidgetStart->getTilePtr()->getOccupant();
    unitPtr->setHasAttacked(true);

    static std::mt19937 randomEngine(std::random_device{}());
    static std::uniform_int_distribution<int> luckDamageDistribution(0, 10);
    int damage = unitPtr->getUnitStats().damage_ + luckDamageDistribution(randomEngine);

    MapHandler* mapHandlerPtr = this->battleWidgetPtr_->getMapWidgetPtr()->getMapHandlerPtr();
    int attackerMorale = mapHandlerPtr->calculateMorale(unitPtr, tileWidgetStart->getTilePtr());
    double moraleMultiplier = 1.0 - (50.0 - attackerMorale) / 100.0;
    damage = static_cast<int>(damage * moraleMultiplier);

    Unit* defenderUnitPtr = tileWidgetDest->getTilePtr()->getOccupant();
    int attackerPlayerIdx = unitPtr->getOwnerPtr()->getPlayerIdx();
    int defenderPlayerIdx = defenderUnitPtr->getOwnerPtr()->getPlayerIdx();
    UnitType defenderUnitType = defenderUnitPtr->getUnitType();
    std::pair<int, int> targetIndex = tileWidgetDest->getTilePtr()->getTileIndex();

    this->logger_.addMessage(std::make_unique<AttackMessage>(attackerPlayerIdx, unitPtr->getUnitType(), defenderPlayerIdx, defenderUnitType, damage, targetIndex));
    this->actionWidgetPtr_->setLastMessage(this->logger_.getLastMessageText());

    if(damage < tileWidgetDest->getTilePtr()->getOccupant()->getRemainingHealth()){
        tileWidgetDest->getTilePtr()->getOccupant()->dealDamage(damage);
        mapHandlerPtr->getUnitWidget(tileWidgetDest->getTilePtr()->getOccupant())->updateHealthLabel();

        int damageDiff = std::abs(damage - tileWidgetDest->getTilePtr()->getOccupant()->getRemainingHealth());

        this->getCurrentPlayerPtr()->addDamageDealt(damageDiff);
        this->getNotCurrentPlayerPtr()->addDamageReceived(damageDiff);

        this->refreshUnitMorale();
    }
    else if(true){
        Unit* deleteUnitPtr = tileWidgetDest->getTilePtr()->getOccupant();
        UnitWidget* deleteUnitWidgetPtr = mapHandlerPtr->getUnitWidget(deleteUnitPtr);
        QGraphicsSimpleTextItem* deleteHealthLabelPtr = deleteUnitWidgetPtr->getHealthLabelPtr();
        QGraphicsSimpleTextItem* deleteMoraleLabelPtr = deleteUnitWidgetPtr->getMoraleLabelPtr();
        delete deleteHealthLabelPtr;
        delete deleteMoraleLabelPtr;

        tileWidgetDest->getTilePtr()->setOccupation(nullptr);

        deleteUnitWidgetPtr->setDeadPixmap();

        this->logger_.addMessage(std::make_unique<KillMessage>(attackerPlayerIdx, unitPtr->getUnitType(), defenderPlayerIdx, defenderUnitType, targetIndex));
        this->actionWidgetPtr_->setLastMessage(this->logger_.getLastMessageText());
        
        this->getCurrentPlayerPtr()->addFrag();
        this->getNotCurrentPlayerPtr()->addCasualty();
        this->getNotCurrentPlayerPtr()->removeUnit(deleteUnitPtr);
        mapHandlerPtr->removeUnitWidget(deleteUnitPtr);

        this->refreshUnitMorale();

        QTimer::singleShot(800, [deleteUnitPtr, deleteUnitWidgetPtr, tileWidgetDest](){
            delete deleteUnitPtr;
            delete deleteUnitWidgetPtr;
        });

        return;
    }
    return;
}

void TurnHandler::endTurn(){
    if(currentPlayerPtr_ == players_.first){
        currentPlayerPtr_ = players_.second;
        this->actionWidgetPtr_->setCurrentPlayerStats(players_.second);
    }
    else if(currentPlayerPtr_ == players_.second){
        currentPlayerPtr_ = players_.first;
        this->actionWidgetPtr_->setCurrentPlayerStats(players_.first);
    }
    this->currentPlayerPtr_->refreshUnitsSpeed();
    this->battleWidgetPtr_->getMapWidgetPtr()->removeAllSelection();
    this->actionMode_ = ActionMode::None;

    if(currentPlayerPtr_->isAI()){
        this->aiHandlerPtr_->executeTurn();
    }

    return;
}

void TurnHandler::moveUnitSlot(){
    this->actionMode_ = ActionMode::MoveUnit;
}

void TurnHandler::attackUnitSlot(){
    this->actionMode_ = ActionMode::AttackUnit;
}

void TurnHandler::recruitUnitSlot(UnitType unitTypeIdx){
    if(currentPlayerPtr_->getGold() >= UnitStatsMap.at(unitTypeIdx).cost_
    && static_cast<int>(currentPlayerPtr_->getUnits().size()) < this->battleSettingPtr_->getMaxUnit()){
        this->shopWidgetPtr_->buyUnit(currentPlayerPtr_, unitTypeIdx);
        this->pendingUnitType_ = unitTypeIdx;
        this->actionMode_ = ActionMode::RecruitUnit;
    }
}

void TurnHandler::endTurnSlot(){
    this->endTurn();
    return;
}

void TurnHandler::confirmUnitDeployment(TileWidget* tileWidgetPtr){
    if(this->actionMode_ == ActionMode::RecruitUnit){
        UnitWidget* unitWidgetPtr = new UnitWidget(this->pendingUnitType_, tileWidgetPtr, new Unit(this->currentPlayerPtr_, this->pendingUnitType_, UnitStatsMap.at(this->pendingUnitType_)));
        this->battleWidgetPtr_->getMapWidgetPtr()->getMapHandlerPtr()->addUnitWidget(unitWidgetPtr);
        tileWidgetPtr->getTilePtr()->setOccupation(unitWidgetPtr->getUnitPtr());
        this->currentPlayerPtr_->addUnit(unitWidgetPtr->getUnitPtr());
        this->actionMode_ = ActionMode::None;
        this->getActionWidgetPtr()->setCurrentPlayerStats(this->currentPlayerPtr_);

        this->logger_.addMessage(std::make_unique<RecruitMessage>(this->currentPlayerPtr_->getPlayerIdx(), this->pendingUnitType_, tileWidgetPtr->getTilePtr()->getTileIndex()));
        this->actionWidgetPtr_->setLastMessage(this->logger_.getLastMessageText());

        this->refreshUnitMorale();
    }
    return;
}

void TurnHandler::setAIHandler(AIHandler* aiHandlerPtr){
    this->aiHandlerPtr_ = aiHandlerPtr;
    return;
}

void TurnHandler::setActionMode(ActionMode actionMode){
    this->actionMode_ = actionMode;
    return;
}

Player* TurnHandler::getPlayerPtr(int playerIdx){
    return playerIdx == 1 ? players_.first : players_.second;
}

ActionWidget* TurnHandler::getActionWidgetPtr(){
    return this->actionWidgetPtr_;
}

Player* TurnHandler::getCurrentPlayerPtr(){
    return this->currentPlayerPtr_;
}

Player* TurnHandler::getNotCurrentPlayerPtr(){
    if(this->getCurrentPlayerPtr()->getPlayerIdx() == 1){
        return this->getPlayerPtr(2);
    }
    else{
        return this->getPlayerPtr(1);
    }
}

Logger* TurnHandler::getLoggerPtr(){
    return &this->logger_;
}

void TurnHandler::refreshUnitMorale(){
    MapHandler* mapHandlerPtr = this->battleWidgetPtr_->getMapWidgetPtr()->getMapHandlerPtr();

    for(Player* playerPtr : {this->players_.first, this->players_.second}){
        for(Unit* unitPtr : playerPtr->getUnits()){
            UnitWidget* unitWidgetPtr = mapHandlerPtr->getUnitWidget(unitPtr);
            Tile* tilePtr = unitWidgetPtr->getTileWidgetPtr()->getTilePtr();
            int morale = mapHandlerPtr->calculateMorale(unitPtr, tilePtr);
            unitWidgetPtr->updateMoraleLabel(morale);
        }
    }
    return;
}

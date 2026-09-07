#include "player.hpp"

Player::Player(int playerIdx, int startColumn) : startColumn_(startColumn) {
    this->gold_ = 300;
    this->playerIdx_ = playerIdx;
}

void Player::refreshUnitsSpeed(){
    for(const auto& unit : this->units_){
        unit->setRemainingSpeed(unit->getUnitStats().speed_);
        unit->setHasAttacked(false);
    }
    return;
}

void Player::addUnit(Unit* unitPtr){
    this->units_.push_back(unitPtr);
    return;
}

void Player::subtractGold(int minus){
    this->gold_ = this->gold_ - minus;
    return;
}

int Player::getGold(){
    return this->gold_;
}

int Player::getPlayerStartColumn() const {
    return this->startColumn_;
}

int Player::getPlayerIdx() const {
    return this->playerIdx_;
}
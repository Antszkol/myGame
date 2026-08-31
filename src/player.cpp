#include "player.hpp"

Player::Player(int playerIdx){
    this->gold_ = 300;   
    this->playerIdx_ = playerIdx;
}

int Player::getGold(){
    return this->gold_;
}

int Player::getPlayerIdx(){
    return this->playerIdx_;
}

void Player::refreshUnitsSpeed(){
    for(const auto& unit : this->units_){
        unit->setRemainingSpeed(unit->getUnitStats().speed_);
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
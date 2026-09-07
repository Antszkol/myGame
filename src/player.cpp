#include "player.hpp"
#include <algorithm>

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
    this->playerStats_.recruitedUnitsCount_++;
    return;
}

void Player::removeUnit(Unit* unitPtr){
    std::erase(units_, unitPtr);
    return;
}

void Player::addCasualty(){
    this->playerStats_.casualtyCount_++;
    return;
};

void Player::addFrag(){
    this->playerStats_.fragCount_++;
    return;
};

void Player::addDamageDealt(int damage){
    this->playerStats_.damageDealt_ = this->playerStats_.damageDealt_ + damage;
    return;
};

void Player::addDamageReceived(int damage){
    this->playerStats_.damageReceived_ = this->playerStats_.damageReceived_ + damage;
    return;
};

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

const std::vector<Unit*>& Player::getUnits() const {
    return this->units_;
}

const PlayerStats& Player::getPlayerStats() const {
    return this->playerStats_;
}
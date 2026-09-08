#include "unit.hpp"
#include "player.hpp"

Unit::Unit(const Player* owner, const UnitType& unitType, const UnitStats& unitStats) :
    ownerPtr_(owner),
    unitStats_(unitStats),
    unitType_(unitType)
{
    this->remainingSpeed_ = this->unitStats_.speed_;
    this->remainingHealth_ = this->unitStats_.health_;
    this->hasAttacked_ = false;
}

void Unit::dealDamage(int damage){
    this->remainingHealth_ = this->remainingHealth_ - damage;
    return;
}

void Unit::subtractSpeed(int subtract){
    this->remainingSpeed_ = this->remainingSpeed_ - subtract;
    return;
}

bool Unit::hasAttacked(){
    return this->hasAttacked_;
}

void Unit::setRemainingSpeed(int speed){
    this->remainingSpeed_ = speed;
    return;
}

void Unit::setHasAttacked(bool hasAttacked){
    this->hasAttacked_ = hasAttacked;
    return;
}

void Unit::setMorale(int morale){
    this->morale_ = morale;
    return;
}

UnitStats Unit::getUnitStats() const {
    return this->unitStats_;
}

int Unit::getHealth(){
    return this->remainingHealth_;
}

int Unit::getRemainingSpeed(){
    return this->remainingSpeed_;
}

int Unit::getRemainingHealth(){
    return this->remainingHealth_;
}

UnitType Unit::getUnitType() const {
    return this->unitType_;
}

const Player* Unit::getOwnerPtr(){
    return this->ownerPtr_;
}
#include "unit.hpp"
#include "player.hpp"

Unit::Unit(const Player* owner, const UnitType& unitType, const UnitStats& unitStats, UnitWidget* const unitWidgetPtr) : 
    ownerPtr_(owner),
    unitStats_(unitStats),
    unitWidgetPtr_(unitWidgetPtr),
    unitType_(unitType)
{
    this->remainingSpeed_ = this->unitStats_.speed_;
    this->remainingHealth_ = this->unitStats_.health_;
}

UnitStats Unit::getUnitStats() const {
    return this->unitStats_;
}

UnitWidget* Unit::getUnitWidgetPtr() const {
    return this->unitWidgetPtr_;
}

int Unit::getHealth(){
    return this->remainingHealth_;
}

void Unit::dealDamage(int damage){
    this->remainingHealth_ = this->remainingHealth_ - damage;
    return;
}

void Unit::setRemainingSpeed(int speed){
    this->remainingSpeed_ = speed;
    return;
}

int Unit::getRemainingSpeed(){
    return this->remainingSpeed_;
}

int Unit::getRemainingHealth(){
    return this->remainingHealth_;
}

void Unit::subtractSpeed(int subtract){
    this->remainingSpeed_ = this->remainingSpeed_ - subtract;
    return;
}

int Unit::getUnitType() const {
    return this->unitType_;
}

const Player* Unit::getOwnerPtr(){
    return this->ownerPtr_;
}
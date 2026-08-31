#include "unit.hpp"

Unit::Unit(const UnitType& unitType, const UnitStats& unitStats, UnitWidget* const unitWidgetPtr) : 
    unitStats_(unitStats),
    unitWidgetPtr_(unitWidgetPtr),
    unitType_(unitType)
{this->remainingSpeed_ = this->unitStats_.speed_;}

UnitStats Unit::getUnitStats() const {
    return this->unitStats_;
}

UnitWidget* Unit::getUnitWidgetPtr() const {
    return this->unitWidgetPtr_;
}

void Unit::setRemainingSpeed(int speed){
    this->remainingSpeed_ = speed;
    return;
}

int Unit::getRemainingSpeed(){
    return this->remainingSpeed_;
}

void Unit::subtractSpeed(int subtract){
    this->remainingSpeed_ = this->remainingSpeed_ - subtract;
    return;
}

int Unit::getUnitType() const {
    return this->unitType_;
}
#include "unit.hpp"

Unit::Unit(const UnitType& unitType, const UnitStats& unitStats, UnitWidget* const unitWidgetPtr) : 
    unitStats_(unitStats),
    unitWidgetPtr_(unitWidgetPtr),
    unitType_(unitType)
{}

UnitStats Unit::getUnitStats() const {
    return this->unitStats_;
}

UnitWidget* Unit::getUnitWidgetPtr() const {
    return this->unitWidgetPtr_;
}

int Unit::getUnitType() const {
    return this->unitType_;
}
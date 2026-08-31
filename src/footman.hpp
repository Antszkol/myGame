#pragma once
#include "unit.hpp"

class Footman : public Unit {
    public:
        Footman(UnitWidget* unitWidgetPtr);

        const int armour_;
};

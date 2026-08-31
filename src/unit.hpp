#pragma once
#include "unitType.hpp"
#include "unitStats.hpp"
#include "unitWidget.hpp"

class Unit {
    public:
        Unit(const UnitType& unitType, const UnitStats& unitStats, UnitWidget* const unitWidgetPtr);

        UnitStats getUnitStats() const;
        int getUnitType() const;
        UnitWidget* getUnitWidgetPtr() const;
        int getRemainingSpeed();
        void subtractSpeed(int subtract);
        void setRemainingSpeed(int speed);

    protected:
        const int unitType_;
        int remainingSpeed_;
        UnitWidget* unitWidgetPtr_;
        const UnitStats unitStats_;  
};
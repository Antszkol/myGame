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

    protected:
        const int unitType_;
        UnitWidget* unitWidgetPtr_;
        const UnitStats unitStats_;  
};
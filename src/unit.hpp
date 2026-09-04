#pragma once
#include "unitType.hpp"
#include "unitStats.hpp"
#include "unitWidget.hpp"

class Player;

class Unit {
    public:
        Unit(const Player* owner, const UnitType& unitType, const UnitStats& unitStats);

        UnitStats getUnitStats() const;
        int getUnitType() const;
        UnitWidget* getUnitWidgetPtr() const;
        int getRemainingSpeed();
        int getRemainingHealth();
        int getHealth();
        void subtractSpeed(int subtract);
        void setRemainingSpeed(int speed);
        void setUnitWidgetPtr(UnitWidget* unitWidgetPtr);
        void dealDamage(int damage);
        const Player* getOwnerPtr();

    protected:
        const int unitType_;
        int remainingSpeed_;
        int remainingHealth_;
        UnitWidget* unitWidgetPtr_;
        const Player* ownerPtr_;
        const UnitStats unitStats_;  
};
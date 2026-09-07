#pragma once
#include "unitType.hpp"
#include "unitStats.hpp"
#include "unitWidget.hpp"

class Player;

class Unit {
    public:
        Unit(const Player* owner, const UnitType& unitType, const UnitStats& unitStats);

        void subtractSpeed(int subtract);
        void dealDamage(int damage);
        bool hasAttacked();

        void setRemainingSpeed(int speed);
        void setUnitWidgetPtr(UnitWidget* unitWidgetPtr);
        void setHasAttacked(bool hasAttacked);

        UnitStats getUnitStats() const;
        UnitType getUnitType() const;
        UnitWidget* getUnitWidgetPtr() const;
        int getRemainingSpeed();
        int getRemainingHealth();
        int getHealth();
        const Player* getOwnerPtr();

    protected:
        const UnitType unitType_;
        int remainingSpeed_;
        int remainingHealth_;
        bool hasAttacked_;
        UnitWidget* unitWidgetPtr_;
        const Player* ownerPtr_;
        const UnitStats unitStats_;
};
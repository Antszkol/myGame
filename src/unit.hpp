#pragma once
#include "unitType.hpp"
#include "unitStats.hpp"

class Player;

/// @brief One combat unit's game-logic state (health, speed, morale). Has no knowledge of
/// UnitWidget or any other Qt type.
class Unit {
    public:
        /// @param owner the player this unit belongs to.
        /// @param unitType the unit's type.
        /// @param unitStats base stats (health/damage/range/speed/cost) for unitType.
        Unit(const Player* owner, const UnitType& unitType, const UnitStats& unitStats);

        /// @brief Subtracts from this turn's remaining movement points.
        /// @param subtract movement points to deduct.
        void subtractSpeed(int subtract);

        /// @brief Reduces remaining health by the given amount (does not clamp at 0; killing is
        /// handled by the caller, see TurnHandler::attackUnit).
        /// @param damage amount of damage to apply.
        void dealDamage(int damage);

        /// @return whether this unit has already attacked this turn.
        bool hasAttacked();

        /// @brief Resets remaining movement points, typically at the start of this unit's turn.
        /// @param speed new remaining speed value.
        void setRemainingSpeed(int speed);

        /// @param hasAttacked new attacked-this-turn flag.
        void setHasAttacked(bool hasAttacked);

        /// @param morale new morale value (see MapHandler::calculateMorale).
        void setMorale(int morale);

        /// @return this unit's base stat block.
        UnitStats getUnitStats() const;

        /// @return this unit's type.
        UnitType getUnitType() const;

        /// @return movement points still available this turn.
        int getRemainingSpeed();

        /// @return current health.
        int getRemainingHealth();

        /// @return maximum/starting health.
        int getHealth();

        /// @return the player who owns this unit.
        const Player* getOwnerPtr();

    protected:
        const UnitType unitType_;
        int remainingSpeed_;
        int remainingHealth_;
        bool hasAttacked_;
        const Player* ownerPtr_;
        const UnitStats unitStats_;
        int morale_ = 0;
};
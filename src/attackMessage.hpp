#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

/// @brief Combat log entry recording a non-lethal attack (the defender survives).
class AttackMessage : public Message {
    public:
        /// @param attackerPlayerIdx index of the attacking player.
        /// @param attackerUnitType type of the attacking unit.
        /// @param defenderPlayerIdx index of the defending player.
        /// @param defenderUnitType type of the defending unit.
        /// @param damage final damage dealt (after luck roll and morale multiplier).
        /// @param targetIndex tile index of the defending unit.
        AttackMessage(int attackerPlayerIdx, UnitType attackerUnitType, int defenderPlayerIdx, UnitType defenderUnitType, int damage, std::pair<int, int> targetIndex);

        std::string describe() const override;

    private:
        int attackerPlayerIdx_;
        UnitType attackerUnitType_;
        int defenderPlayerIdx_;
        UnitType defenderUnitType_;
        int damage_;
        std::pair<int, int> targetIndex_;
};

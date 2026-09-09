#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

/// @brief Combat log entry recording an attack that kills the defending unit.
class KillMessage : public Message {
    public:
        /// @param killerPlayerIdx index of the attacking player.
        /// @param killerUnitType type of the attacking unit.
        /// @param victimPlayerIdx index of the defeated player.
        /// @param victimUnitType type of the defeated unit.
        /// @param tileIndex tile index where the kill happened.
        KillMessage(int killerPlayerIdx, UnitType killerUnitType, int victimPlayerIdx, UnitType victimUnitType, std::pair<int, int> tileIndex);

        std::string describe() const override;

    private:
        int killerPlayerIdx_;
        UnitType killerUnitType_;
        int victimPlayerIdx_;
        UnitType victimUnitType_;
        std::pair<int, int> tileIndex_;
};

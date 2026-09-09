#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

/// @brief Combat log entry recording a unit moving from one tile to another.
class MoveMessage : public Message {
    public:
        /// @param playerIdx index of the player who owns the moved unit.
        /// @param unitType type of the moved unit.
        /// @param fromIndex tile index the unit moved from.
        /// @param toIndex tile index the unit moved to.
        MoveMessage(int playerIdx, UnitType unitType, std::pair<int, int> fromIndex, std::pair<int, int> toIndex);

        std::string describe() const override;

    private:
        int playerIdx_;
        UnitType unitType_;
        std::pair<int, int> fromIndex_;
        std::pair<int, int> toIndex_;
};

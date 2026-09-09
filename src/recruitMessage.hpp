#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

/// @brief Combat log entry recording a unit being deployed onto the map.
class RecruitMessage : public Message {
    public:
        /// @param playerIdx index of the player who recruited the unit.
        /// @param unitType type of the recruited unit.
        /// @param tileIndex tile index the unit was deployed to.
        RecruitMessage(int playerIdx, UnitType unitType, std::pair<int, int> tileIndex);

        std::string describe() const override;

    private:
        int playerIdx_;
        UnitType unitType_;
        std::pair<int, int> tileIndex_;
};

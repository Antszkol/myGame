#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

class KillMessage : public Message {
    public:
        KillMessage(int killerPlayerIdx, UnitType killerUnitType, int victimPlayerIdx, UnitType victimUnitType, std::pair<int, int> tileIndex);

        std::string describe() const override;

    private:
        int killerPlayerIdx_;
        UnitType killerUnitType_;
        int victimPlayerIdx_;
        UnitType victimUnitType_;
        std::pair<int, int> tileIndex_;
};

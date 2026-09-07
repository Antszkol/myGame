#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

class AttackMessage : public Message {
    public:
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

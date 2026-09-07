#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

class RecruitMessage : public Message {
    public:
        RecruitMessage(int playerIdx, UnitType unitType, std::pair<int, int> tileIndex);

        std::string describe() const override;

    private:
        int playerIdx_;
        UnitType unitType_;
        std::pair<int, int> tileIndex_;
};

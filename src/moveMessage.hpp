#pragma once
#include <utility>
#include "message.hpp"
#include "unitType.hpp"

class MoveMessage : public Message {
    public:
        MoveMessage(int playerIdx, UnitType unitType, std::pair<int, int> fromIndex, std::pair<int, int> toIndex);

        std::string describe() const override;

    private:
        int playerIdx_;
        UnitType unitType_;
        std::pair<int, int> fromIndex_;
        std::pair<int, int> toIndex_;
};

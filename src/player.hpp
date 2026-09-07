#pragma once
#include "unit.hpp"
#include <vector>

class Player {
    public:
        Player(int playerIdx, int startColumn);

        void subtractGold(int minus);
        void refreshUnitsSpeed();
        void addUnit(Unit* unitPtr);

        int getGold();
        int getPlayerIdx() const;
        int getPlayerStartColumn() const;

    private:
        std::vector<Unit*> units_;
        int gold_;
        int playerIdx_;
        const int startColumn_;
};
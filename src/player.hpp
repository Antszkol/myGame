#pragma once
#include "unit.hpp"
#include <vector>

class Player {
    public:
        Player(int playerIdx, int startColumn);

        int getGold();
        int getPlayerIdx();
        const int getPlayerStartColumn();
        void subtractGold(int minus);

        void refreshUnitsSpeed();
        void addUnit(Unit* unitPtr);

    private:
        std::vector<Unit*> units_;
        int gold_;
        int playerIdx_;
        const int startColumn_;
};
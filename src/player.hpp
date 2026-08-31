#pragma once
#include "unit.hpp"
#include <vector>

class Player {
    public:
        Player(int playerIdx);

        int getGold();
        int getPlayerIdx();
        void subtractGold(int minus);

    private:
        std::vector<Unit*> units_;
        int gold_;
        int playerIdx_;
};
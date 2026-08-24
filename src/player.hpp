#pragma once
#include "unit.hpp"
#include <vector>

class Player {
    public:
        Player();

        int getGold();
        void subtractGold(int minus);

    private:
        std::vector<Unit*> units_;
        int gold_;
};
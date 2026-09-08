#pragma once

#include <string>
#include <utility>
#include <vector>

#include "gameMode.hpp"

using namespace std;

class BattleSetting{
    public:
        BattleSetting();

        void saveBattleSettings(int newStartGold, int newMaxUnit, GameMode newGameMode);

        // const after getters to ensure they don't modify the object
        int getMaxUnit() const;
        int getStartGold() const;
        GameMode getGameMode() const;

    private:
        int maxUnit_;
        int startGold_;
        GameMode gameMode_;
};
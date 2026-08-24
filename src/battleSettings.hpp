#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class BattleSetting{
    public:
        BattleSetting();

        void saveBattleSettings(int newStartGold, int newMaxUnit);

        // const after getters to ensure they don't modify the object
        int getMaxUnit() const;
        int getStartGold() const;

    private:
        int maxUnit_;
        int startGold_;
};
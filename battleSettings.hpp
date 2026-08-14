#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class battleSetting{
    public:
        void saveBattleSettings(int newStartGold, int newMaxUnit);

        // const after getters to ensure they don't modify the object
        int getMaxUnit() const;
        int getStartGold() const;

    private:
        int maxUnit;
        int startGold;
};

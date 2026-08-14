#include "battleSettings.hpp"

void battleSetting::saveBattleSettings(int newStartGold, int newMaxUnit){
    startGold = newStartGold;
    maxUnit = newMaxUnit;
}

int battleSetting::getStartGold() const {
    return startGold;
}

int battleSetting::getMaxUnit() const {
    return maxUnit;
}
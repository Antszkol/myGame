#include "battleSettings.hpp"

BattleSetting::BattleSetting(){
    startGold_ = 100;
    maxUnit_ = 12;  
    return;    
}

void BattleSetting::saveBattleSettings(int newStartGold, int newMaxUnit){
    startGold_ = newStartGold;
    maxUnit_ = newMaxUnit;
}

int BattleSetting::getStartGold() const {
    return startGold_;
}

int BattleSetting::getMaxUnit() const {
    return maxUnit_;
}
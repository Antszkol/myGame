#include "battleSettings.hpp"

BattleSetting::BattleSetting(){
    startGold_ = 100;
    maxUnit_ = 12;
    gameMode_ = GameMode::HotSeat;
    return;
}

void BattleSetting::saveBattleSettings(int newStartGold, int newMaxUnit, GameMode newGameMode){
    startGold_ = newStartGold;
    maxUnit_ = newMaxUnit;
    gameMode_ = newGameMode;
}

int BattleSetting::getStartGold() const {
    return startGold_;
}

int BattleSetting::getMaxUnit() const {
    return maxUnit_;
}

GameMode BattleSetting::getGameMode() const {
    return gameMode_;
}
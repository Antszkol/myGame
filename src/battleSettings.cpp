#include "battleSettings.hpp"

BattleSetting::BattleSetting(){
    startGold_ = 300;
    maxUnit_ = 12;
    gameMode_ = GameMode::HotSeat;
    mapType_ = mapType::river;
    return;
}

void BattleSetting::saveBattleSettings(int newStartGold, int newMaxUnit, GameMode newGameMode, mapType newMapType){
    startGold_ = newStartGold;
    maxUnit_ = newMaxUnit;
    gameMode_ = newGameMode;
    mapType_ = newMapType;
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

mapType BattleSetting::getMapType() const {
    return mapType_;
}
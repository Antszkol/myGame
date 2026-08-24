#include "battle.hpp"

Battle::Battle(Map* map, BattleSetting* battleSettingPtr){
    this->mapPtr_ = map;
    this->battleSettingPtr_ = battleSettingPtr;
}

Map* Battle::getMap(){
    return this->mapPtr_;
}

BattleSetting* Battle::getBattleSetting(){
    return this->battleSettingPtr_;
}
#include "attackMessage.hpp"
#include <sstream>

AttackMessage::AttackMessage(int attackerPlayerIdx, UnitType attackerUnitType, int defenderPlayerIdx, UnitType defenderUnitType, int damage, std::pair<int, int> targetIndex){
    this->attackerPlayerIdx_ = attackerPlayerIdx;
    this->attackerUnitType_ = attackerUnitType;
    this->defenderPlayerIdx_ = defenderPlayerIdx;
    this->defenderUnitType_ = defenderUnitType;
    this->damage_ = damage;
    this->targetIndex_ = targetIndex;
}

std::string AttackMessage::describe() const{
    std::ostringstream out;
    out << "Player " << this->attackerPlayerIdx_ << "'s " << UnitTypeMap.at(this->attackerUnitType_)
        << " attacked Player " << this->defenderPlayerIdx_ << "'s " << UnitTypeMap.at(this->defenderUnitType_)
        << " at (" << this->targetIndex_.first << ", " << this->targetIndex_.second << ")"
        << " for " << this->damage_ << " damage";
    return out.str();
}

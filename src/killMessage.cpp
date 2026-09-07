#include "killMessage.hpp"
#include <sstream>

KillMessage::KillMessage(int killerPlayerIdx, UnitType killerUnitType, int victimPlayerIdx, UnitType victimUnitType, std::pair<int, int> tileIndex){
    this->killerPlayerIdx_ = killerPlayerIdx;
    this->killerUnitType_ = killerUnitType;
    this->victimPlayerIdx_ = victimPlayerIdx;
    this->victimUnitType_ = victimUnitType;
    this->tileIndex_ = tileIndex;
}

std::string KillMessage::describe() const{
    std::ostringstream out;
    out << "Player " << this->killerPlayerIdx_ << "'s " << UnitTypeMap.at(this->killerUnitType_) << " killed Player " << this->victimPlayerIdx_ << "'s "
        << UnitTypeMap.at(this->victimUnitType_)
        << " at (" << this->tileIndex_.first << ", " << this->tileIndex_.second << ")";
    return out.str();
}

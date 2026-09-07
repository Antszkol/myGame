#include "recruitMessage.hpp"
#include <sstream>

RecruitMessage::RecruitMessage(int playerIdx, UnitType unitType, std::pair<int, int> tileIndex){
    this->playerIdx_ = playerIdx;
    this->unitType_ = unitType;
    this->tileIndex_ = tileIndex;
}

std::string RecruitMessage::describe() const{
    std::ostringstream out;
    out << "Player " << this->playerIdx_ << " deployed a " << UnitTypeMap.at(this->unitType_)
        << " at tile (" << this->tileIndex_.first << ", " << this->tileIndex_.second << ")";
    return out.str();
}

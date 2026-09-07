#include "moveMessage.hpp"
#include <sstream>

MoveMessage::MoveMessage(int playerIdx, UnitType unitType, std::pair<int, int> fromIndex, std::pair<int, int> toIndex){
    this->playerIdx_ = playerIdx;
    this->unitType_ = unitType;
    this->fromIndex_ = fromIndex;
    this->toIndex_ = toIndex;
}

std::string MoveMessage::describe() const{
    std::ostringstream out;
    out << "Player " << this->playerIdx_ << "'s " << UnitTypeMap.at(this->unitType_)
        << " moved from tile (" << this->fromIndex_.first << ", " << this->fromIndex_.second << ")"
        << " to tile (" << this->toIndex_.first << ", " << this->toIndex_.second << ")";
    return out.str();
}

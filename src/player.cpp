#include "player.hpp"

Player::Player(int playerIdx){
    this->gold_ = 300;   
    this->playerIdx_ = playerIdx;
}

int Player::getGold(){
    return this->gold_;
}

int Player::getPlayerIdx(){
    return this->playerIdx_;
}

void Player::subtractGold(int minus){
    this->gold_ = this->gold_ - minus;
    return;
}
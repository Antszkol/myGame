#include "player.hpp"

Player::Player(){
    this->gold_ = 100;   
}

int Player::getGold(){
    return this->gold_;
}

void Player::subtractGold(int minus){
    this->gold_ = this->gold_ - minus;
    return;
}
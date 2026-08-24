#include "tile.hpp"
#include "tileType.hpp"

// tileType_ ustawia sie w konstruktorze, musimy go z

Tile::Tile(pair<int, int> tileIndex, int tileType) : 
    tileIndex_(tileIndex), 
    tileType_(tileType),
    speedImpact_(1),
    moraleImpact_(0),
    isOccupied_(false)
    {};

void Tile::setOccupation(bool trueFalse){
    this->isOccupied_ = trueFalse;
    return;
}

bool Tile::isPassable(){
    if(this->isOccupied_) return false;
    else return true;
}

int Tile::getTileType() const {
    return this->tileType_;
}

pair<int, int> Tile::getTileIndex(){
    return this->tileIndex_;
}
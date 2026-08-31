#include "tile.hpp"
#include "tileType.hpp"

// tileType_ ustawia sie w konstruktorze, musimy go z

Tile::Tile(pair<int, int> tileIndex, int tileType) : 
    tileIndex_(tileIndex), 
    tileType_(tileType),
    speedImpact_(1),
    moraleImpact_(0)
    {
        occupant_ = nullptr;
    };

void Tile::setOccupation(Unit* occupant){
    this->occupant_ = occupant;
    return;
}

int Tile::getSpeedImpact() const {
    return this->speedImpact_;
}

bool Tile::isPassable(){
    if(this->occupant_ != nullptr) return false;
    else return true;
}

Unit* Tile::getOccupant() const {
    return this->occupant_;
}

bool Tile::isOccupied(){
    if(this->occupant_ != nullptr) return true;
    else return false;
}

TileWidget* Tile::getTileWidgetPtr(){
    return this->tileWidgetPtr_;
}

void Tile::setWalkability(bool boolean){
    this->isWalkable_ = boolean;
}

void Tile::setTileWidget(TileWidget* tileWidgetPtr){
    this->tileWidgetPtr_ = tileWidgetPtr;
}

int Tile::getTileType() const {
    return this->tileType_;
}

pair<int, int> Tile::getTileIndex(){
    return this->tileIndex_;
}
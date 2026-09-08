#include "tile.hpp"
#include "tileType.hpp"
#include "player.hpp"

// tileType_ ustawia sie w konstruktorze, musimy go z

Tile::Tile(pair<int, int> tileIndex, int tileType) :
    tileIndex_(tileIndex),
    tileType_(tileType),
    speedImpact_(1),
    moraleImpact_(0)
    {
        occupant_ = nullptr;
    };

bool Tile::isWithinDeploymentZone(const Player* playerPtr){
    if(std::abs(this->getTileIndex().first - playerPtr->getPlayerStartColumn()) < 2){
        return true;
    }
    return false;
}

bool Tile::isPassable(){
    if(this->occupant_ != nullptr || this->getTileType() == TileType::water) return false;
    else return true;
}

bool Tile::isPassableTerrain() const {
    if(this->getTileType() == TileType::water) return false;
    else return true;
}

bool Tile::isOccupied(){
    if(this->occupant_ != nullptr) return true;
    else return false;
}

void Tile::setOccupation(Unit* occupant){
    this->occupant_ = occupant;
    return;
}

int Tile::getSpeedImpact() const {
    return this->speedImpact_;
}

Unit* Tile::getOccupant() const {
    return this->occupant_;
}

int Tile::getTileType() const {
    return this->tileType_;
}

pair<int, int> Tile::getTileIndex(){
    return this->tileIndex_;
}
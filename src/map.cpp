#include <utility>

#include "map.hpp"
#include "tile.hpp"
#include "mapTiles.hpp"


Map::Map(pair<int, int> argMapSize){
    this->mapSize_ = argMapSize;
    this->loadMap();
}

void Map::loadMap(){
    for(int i = 0; i < this->mapSize_.first * this->mapSize_.second; i++){
        pair<int, int> idx;
        idx.first = i % this->mapSize_.first;
        idx.second = i / this->mapSize_.first;
        this->mapTiles_.push_back(new Tile(idx, mapTiles::river[i]));
    }
}

Tile* Map::getTileByIndex(pair<int, int> argTileIndex) const {
    return this->mapTiles_[argTileIndex.first * this->getMapSize().first + argTileIndex.second];
}

pair<int, int> Map::getMapSize() const {
    return mapSize_;
}
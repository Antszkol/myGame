#include <utility>

#include "map.hpp"
#include "tile.hpp"
#include "mapTiles.hpp"


Map::Map(mapType type){
    this->loadMap(type);
}

void Map::loadMap(mapType type){
    const MapLayout& layout = (type == mapType::bog) ? mapTiles::bog : mapTiles::river;
    this->mapSize_ = layout.second;

    for(int i = 0; i < this->mapSize_.first * this->mapSize_.second; i++){
        pair<int, int> idx;
        idx.first = i % this->mapSize_.first;
        idx.second = i / this->mapSize_.first;
        this->mapTiles_.push_back(new Tile(idx, layout.first[i]));
    }
}

bool Map::areTilesAdjacent(Tile* baseTilePtr, Tile* neighbourTilePtr){
    pair<int, int> baseTileIdx = baseTilePtr->getTileIndex();
    pair<int, int> neighbourTileIdx = neighbourTilePtr->getTileIndex();
    if((std::abs(neighbourTileIdx.first - baseTileIdx.first) == 1 && neighbourTileIdx.second == baseTileIdx.second) || (std::abs(neighbourTileIdx.second - baseTileIdx.second) == 1 && neighbourTileIdx.first == baseTileIdx.first)){
        return true;
    }
    else{
        return false;
    }
}

vector<Tile*> Map::getMapTiles(){
    return this->mapTiles_;
}

vector<Tile*> Map::getTileNeighbours(Tile* baseTilePtr){
    std::vector<Tile*> neighbourTiles;
    for(const auto& neighbourTilePtr : this->mapTiles_){
        if(areTilesAdjacent(baseTilePtr, neighbourTilePtr)){
            neighbourTiles.push_back(neighbourTilePtr);
        }
    }
    return neighbourTiles;
}

vector<Tile*> Map::getTileSurrounding(Tile* baseTilePtr){
    std::vector<Tile*> neighbourTiles;
    for(const auto& neighbourTilePtr : this->mapTiles_){
        pair<int, int> baseTileIdx = baseTilePtr->getTileIndex();
        pair<int, int> neighbourTileIdx = neighbourTilePtr->getTileIndex();
        bool isSurrounding;

        if((std::abs(neighbourTileIdx.first - baseTileIdx.first) <= 1) && (std::abs(neighbourTileIdx.second - baseTileIdx.second) <= 1) && (neighbourTilePtr != baseTilePtr)){
            isSurrounding = true;
        }
        else{
            isSurrounding = false;
        }

        if(isSurrounding){
            neighbourTiles.push_back(neighbourTilePtr);
        }
    }
    return neighbourTiles;
}

Tile* Map::getTileByIndex(pair<int, int> argTileIndex) const {
    return this->mapTiles_[argTileIndex.second * this->getMapSize().first + argTileIndex.first];
}

pair<int, int> Map::getMapSize() const {
    return mapSize_;
}

#include "finder.hpp"

Finder::Finder(Map& map) : map_(map){
    return;
};

std::map<Tile*, int> Finder::findMovePaths(Tile* startingTile, int speed){
    pair<int, int> tileIdx = startingTile->getTileIndex();
    std::map<Tile*, int> distMap;

    for(const auto& tile : this->map_.getMapTiles()){
        if(std::abs(tileIdx.first - tile->getTileIndex().first) <= speed && std::abs(tileIdx.second - tile->getTileIndex().second) <= speed){
            distMap.insert({tile, 1000000});
        }
    }

    std::queue<std::pair<Tile*, int>> prioQueue;
    prioQueue.push(std::pair<Tile*, int>(startingTile, 0));
    distMap[startingTile] = 0;

    while(!prioQueue.empty()){
        auto [tile, dist] = prioQueue.front();
        prioQueue.pop();

        if(dist > distMap.at(tile)){
            continue;
        }

        //first, check if all neighbours are in the map
        std::vector<Tile*> neighbourTiles = this->map_.getTileNeighbours(tile);
        std::vector<Tile*> validNeighbourTiles;
        
        for(const auto& neighbourTile : neighbourTiles){
            if(distMap.contains(neighbourTile)){  
                validNeighbourTiles.push_back(neighbourTile);
            }
        }

        for(const auto& neighbourTile : validNeighbourTiles){
            if((dist + tile->getSpeedImpact() < distMap.at(neighbourTile))){
                distMap[neighbourTile] = dist + tile->getSpeedImpact();
                prioQueue.push(std::pair<Tile*, int>(neighbourTile, distMap.at(neighbourTile)));
            }
        }
    }

    return distMap;
};

std::vector<Tile*> Finder::FindTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr){
    pair<int, int> tileIdx = startingTilePtr->getTileIndex();
    std::map<Tile*, int> distMap;

    for(const auto& tile : this->map_.getMapTiles()){
        if(std::abs(tileIdx.first - tile->getTileIndex().first) <= range && std::abs(tileIdx.second - tile->getTileIndex().second) <= range){
            distMap.insert({tile, 1000000});
        }
    }

    std::queue<std::pair<Tile*, int>> prioQueue;
    prioQueue.push(std::pair<Tile*, int>(startingTilePtr, 0));
    distMap[startingTilePtr] = 0;

    while(!prioQueue.empty()){
        auto [tile, dist] = prioQueue.front();
        prioQueue.pop();

        if(dist > distMap.at(tile)){
            continue;
        }

        //first, check if all neighbours are in the map
        std::vector<Tile*> neighbourTiles = this->map_.getTileNeighbours(tile);
        std::vector<Tile*> validNeighbourTiles;
        
        for(const auto& neighbourTile : neighbourTiles){
            if(distMap.contains(neighbourTile)){  
                validNeighbourTiles.push_back(neighbourTile);
            }
        }

        for(const auto& neighbourTile : validNeighbourTiles){
            // 1 since map type should affect unit's range
            if((dist + 1 < distMap.at(neighbourTile))){
                distMap[neighbourTile] = dist + 1;
                prioQueue.push(std::pair<Tile*, int>(neighbourTile, distMap.at(neighbourTile)));
            }
        }
    }

    std::vector<Tile*> tileTargets;

    for(const auto& [tilePtr, dist] : distMap){
        if(tilePtr->getOccupant() != nullptr){
            if(tilePtr->getOccupant()->getOwnerPtr() != currentPlayerPtr){
                tileTargets.push_back(tilePtr);
            }
        }
    }

    return tileTargets;
}
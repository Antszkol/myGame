#include "finder.hpp"

Finder::Finder(Map& map) : map_(map){
    return;
};

std::map<Tile*, int> Finder::findMovePaths(Tile* startingTile, UnitStats unitStats){
    pair<int, int> tileIdx = startingTile->getTileIndex();
    std::map<Tile*, int> distMap;

    for(const auto& tile : this->map_.getMapTiles()){
        if(std::abs(tileIdx.first - tile->getTileIndex().first) < unitStats.speed_ && std::abs(tileIdx.second - tile->getTileIndex().second) < unitStats.speed_){
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

/*
    DIJKSTRA:

    Create a distance queue with all tiles within the unit's speed (don't load all the tiles)
    Create a distance queue for all the tiles withint he range

    Create a priority queue, (fill it with pairs<tile, distance> later, with distance set to infinite value by default)

    Pop the first element from priority queue, for each adjacent tile, if tile distance + edge weight < adjacent tile distance,
    update adjacent tile distance to distance + edge weight. Insert {distance[adjacent tile], adjacent tile} into the priority queue.
*/
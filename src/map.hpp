#pragma once
#include <string>
#include <utility>
#include <vector>
#include "tile.hpp"

using namespace std;

class Map{
    public:
        Map(pair<int, int> argMapSize);
        pair<int, int> getMapSize() const;
        Tile* getTileByIndex(pair<int, int> argTileIndex) const;

    private:
        pair<int, int> mapSize_;
        vector<Tile*> mapTiles_;

        void loadMap();
};

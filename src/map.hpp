#pragma once
#include <string>
#include <utility>
#include <vector>
#include "tile.hpp"
#include "mapType.hpp"

using namespace std;

/// @brief Owns the full grid of Tile objects for one battle map.
class Map{
    public:
        /// @param type which predefined layout (see mapTiles.hpp) to build; also determines the
        /// map's (columns, rows) size, taken from that layout.
        Map(mapType type);

        /// @param baseTilePtr first tile.
        /// @param neighbourTilePtr second tile.
        /// @return whether the two tiles are orthogonally adjacent.
        bool areTilesAdjacent(Tile* baseTilePtr, Tile* neighbourTilePtr);

        /// @return the (columns, rows) size of this map.
        pair<int, int> getMapSize() const;

        /// @param argTileIndex (column, row) grid index to look up.
        /// @return the tile at that index.
        Tile* getTileByIndex(pair<int, int> argTileIndex) const;

        /// @return every tile on the map.
        vector<Tile*> getMapTiles();

        /// @param baseTile tile to find neighbours of.
        /// @return the up-to-4 orthogonally adjacent tiles (used for BFS pathfinding, see Finder).
        vector<Tile*> getTileNeighbours(Tile* baseTile);

        /// @param baseTile tile to find neighbours of.
        /// @return the up-to-8 surrounding tiles, including diagonals (used for morale, see
        /// MapHandler::calculateMorale).
        vector<Tile*> getTileSurrounding(Tile* baseTile);

    private:
        /// @brief Populates mapTiles_ and mapSize_ from the given predefined layout (see mapTiles.hpp).
        /// @param type which layout to load.
        void loadMap(mapType type);

        pair<int, int> mapSize_;
        vector<Tile*> mapTiles_;
};

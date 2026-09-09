#pragma once
#include <queue>
#include <map>
#include "tileType.hpp"
#include "tile.hpp"
#include "map.hpp"
#include "unitStats.hpp"
#include "turnHandler.hpp"

/// @brief BFS pathfinding/reachability queries over a Map, used for both movement and attack range.
class Finder{
    public:
        /// @param map the map to search over.
        Finder(Map& map);

        /// @brief BFS reachability from startingTile, bounded by speed movement points.
        /// @param startingTile tile to search from.
        /// @param speed maximum movement points to spend.
        /// @param ignoreUnits when true, treats occupied tiles as passable (used for AI distance
        /// heuristics, where real movement legality doesn't matter — see AIHandler).
        /// @return every reached tile mapped to its BFS distance from startingTile.
        std::map<Tile*, int> findMovePaths(Tile* startingTile, int speed, bool ignoreUnits = false);

        /// @param startingTilePtr tile to search from (the attacking unit's tile).
        /// @param range maximum attack range.
        /// @param currentPlayerPtr the attacking player, used to filter to enemy-occupied tiles.
        /// @return every enemy-occupied tile within range.
        std::vector<Tile*> FindTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr);

        /// @param unitPtr unit to compute morale for.
        /// @param tilePtr tile the unit stands on.
        /// @return the computed morale value.
        int calculateMorale(Unit* unitPtr, Tile* tilePtr);

    private:
        Map& map_;
        UnitStats currentUnitStats_;
};
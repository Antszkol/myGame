#pragma once
#include <string>
#include <utility>
#include <vector>

#include "unit.hpp"

using namespace std;

/// @brief One map cell's game-logic state (terrain, occupant). Has no knowledge of TileWidget or
/// any other Qt type — see MapHandler for the logic<->UI lookup.
class Tile{
    public:
        /// @param pair (column, row) index of this tile on the map grid.
        /// @param tileType this tile's TileType.
        Tile(pair<int, int> pair, int tileType);

        /// @return whether a unit could currently move onto this tile (terrain AND no occupant).
        bool isPassable();

        /// @return whether this tile's terrain alone allows movement, ignoring any occupant.
        bool isPassableTerrain() const;

        /// @return whether a unit currently occupies this tile.
        bool isOccupied();

        /// @param playerPtr the player to check deployment eligibility for.
        /// @return whether this tile is within playerPtr's deployment zone.
        bool isWithinDeploymentZone(const Player* playerPtr);

        /// @param index new (column, row) grid index for this tile.
        void setIndex(pair<int, int> index);

        /// @param tileType new TileType for this tile.
        void setTileType(int tileType);

        /// @param occupant unit now occupying this tile, or nullptr to clear it.
        void setOccupation(Unit* occupant);

        /// @return this tile's (column, row) grid index.
        pair<int, int> getTileIndex();

        /// @return this tile's TileType.
        int getTileType() const;

        /// @return this tile's movement-cost modifier.
        int getSpeedImpact() const;

        /// @return the unit currently occupying this tile, or nullptr if empty.
        Unit* getOccupant() const;

    private:
        const pair<int, int> tileIndex_;
        const int speedImpact_;
        const int moraleImpact_;
        const int tileType_;

        Unit* occupant_;
};
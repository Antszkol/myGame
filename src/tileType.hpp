#pragma once
/// @brief Terrain type of a single map Tile; affects passability and combat.
enum TileType{
    grass,     ///< Default passable terrain, no gameplay effect.
    water,     ///< Impassable to units.
    mud,       ///< Passable but reduces morale of units standing on it.
    barricade, ///< Reserved for a planned cover mechanic; not yet used in gameplay.
};
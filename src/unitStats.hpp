#pragma once
#include "unitType.hpp"

/// @brief Base stat block for one UnitType (looked up from UnitStatsMap, not stored per-unit).
struct UnitStats {
    int
    health_,   ///< Starting/maximum health.
    damage_,   ///< Base damage dealt per attack, before the random luck roll and morale multiplier.
    range_,    ///< Maximum attack range in tiles (Chebyshev/BFS distance, see Finder).
    speed_,    ///< Movement points available per turn.
    cost_;     ///< Gold cost to recruit one unit of this type.
};

/// @brief Base UnitStats for every UnitType, indexed by unit type.
inline std::map<UnitType, UnitStats> UnitStatsMap = {
    {UnitType::footman, {100, 45, 1, 2, 25}},
    {UnitType::archer, {70, 30, 3, 3, 20}}
};
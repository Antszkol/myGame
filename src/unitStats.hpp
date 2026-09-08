#pragma once
#include "unitType.hpp"

struct UnitStats {
    int unitType_,
    health_,
    damage_,
    range_,
    speed_,
    cost_;
};

inline std::map<UnitType, UnitStats> UnitStatsMap = {
    {UnitType::footman, {0, 100, 45, 1, 2, 25}},
    {UnitType::archer, {1, 70, 30, 3, 3, 20}}
};
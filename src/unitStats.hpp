#pragma once

struct UnitStats {
    int unitType_,
    health_,
    damage_,
    range_,
    speed_,
    cost_;
};

const UnitStats footmanStats = {0, 100, 40, 1, 1, 25};

inline std::map<UnitType, UnitStats> UnitStatsMap = {
    {UnitType::footman, {0, 100, 40, 1, 1, 25}},
    {UnitType::archer, {1, 80, 30, 3, 2, 20}}
};
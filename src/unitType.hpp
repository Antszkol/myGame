#pragma once
#include <array>
#include <map>
#include <string>

/// @brief Combat unit type; determines base UnitStats (see unitStats.hpp) and sprite.
enum UnitType{
    footman,
    archer,
};

/// @brief Human-readable label for each UnitType, used in the UI.
inline std::map<UnitType, std::string> UnitTypeMap = {
    {UnitType::footman, "Footmen"},
    {UnitType::archer, "Archer"}
};
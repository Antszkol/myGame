#pragma once
#include <array>
#include <map>
#include <string>

enum UnitType{
    footman,
    archer,
};

inline std::map<UnitType, std::string> UnitTypeMap = {
    {UnitType::footman, "Footmen"},
    {UnitType::archer, "Archer"}
};
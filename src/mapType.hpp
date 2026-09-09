#pragma once
#include <map>
#include <string>

/// @brief Selects which predefined tile layout (see mapTiles.hpp) a Map is built from. Values
/// must match the layouts actually defined in mapTiles.hpp.
enum mapType{
    river,
    bog,
};

/// @brief Human-readable label for each mapType, used in the UI.
inline std::map<mapType, std::string> MapTypeMap = {
    {mapType::river, "River"},
    {mapType::bog, "Bog"}
};
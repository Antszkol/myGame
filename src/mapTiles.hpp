#pragma once
#include <utility>
#include <vector>

/// @brief One predefined map layout: a row-major flat vector of TileType ints, paired with the
/// (columns, rows) size that vector is laid out as (so a layout carries its own shape — Map no
/// longer needs a separate, independently-specified size).
using MapLayout = std::pair<std::vector<int>, std::pair<int, int>>;

/// @brief Predefined, hardcoded map layouts, read by Map's constructor.
namespace mapTiles {
    /// @brief 10x10 layout with a water river running through the middle.
    inline MapLayout river = {
        {
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 2, 2, 2, 2, 0, 0, 0,
            0, 0, 0, 2, 2, 2, 2, 0, 0, 0,
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 2, 2, 2, 2, 0, 0, 0,
            0, 0, 0, 2, 2, 2, 2, 0, 0, 0,
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0,
            0, 0, 0, 2, 1, 1, 2, 0, 0, 0
        },
        {10, 10}
    };

    /// @brief 8x8 layout with a large water bog in the center.
    inline MapLayout bog = {
        {
            0, 0, 0, 2, 2, 0, 0, 0,
            0, 0, 2, 2, 2, 2, 0, 0,
            0, 2, 2, 2, 2, 2, 2, 0,
            0, 2, 2, 2, 2, 2, 2, 0,
            0, 2, 2, 2, 2, 2, 2, 0,
            0, 2, 2, 2, 2, 2, 2, 0,
            0, 0, 2, 2, 2, 2, 0, 0,
            0, 0, 0, 2, 2, 0, 0, 0
        },
        {8, 8}
    };
}
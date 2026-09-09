#pragma once

#include <string>
#include <utility>
#include <vector>

#include "gameMode.hpp"
#include "mapType.hpp"

using namespace std;

/// @brief Configurable rules for one battle: starting gold, max units per player, game mode, and map.
class BattleSetting{
    public:
        /// @brief Initializes to default settings (300 gold, 12 units, hot-seat, river map).
        BattleSetting();

        /// @param newStartGold new starting gold per player.
        /// @param newMaxUnit new maximum units per player.
        /// @param newGameMode new game mode.
        /// @param newMapType new map layout.
        void saveBattleSettings(int newStartGold, int newMaxUnit, GameMode newGameMode, mapType newMapType);

        // const after getters to ensure they don't modify the object
        /// @return maximum units allowed per player.
        int getMaxUnit() const;
        /// @return starting gold per player.
        int getStartGold() const;
        /// @return the configured game mode.
        GameMode getGameMode() const;
        /// @return the configured map layout.
        mapType getMapType() const;

    private:
        int maxUnit_;
        int startGold_;
        GameMode gameMode_;
        mapType mapType_;
};
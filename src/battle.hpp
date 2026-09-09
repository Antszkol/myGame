#pragma once
#include "map.hpp"
#include "battleSettings.hpp"

/// @brief Bundles a Map with its BattleSetting for one battle instance.
class Battle{
    public:
        /// @param map the map this battle is played on.
        /// @param battleSettingPtr the settings this battle was configured with.
        Battle(Map* map, BattleSetting* battleSettingPtr);

        /// @return the map this battle is played on.
        Map* getMap();

        /// @return the settings this battle was configured with.
        BattleSetting* getBattleSetting();

    private:
        Map* mapPtr_;
        BattleSetting* battleSettingPtr_;
};
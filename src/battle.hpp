#pragma once
#include "map.hpp"
#include "battleSettings.hpp"

class Battle{
    public:
        Battle(Map* map, BattleSetting* battleSettingPtr);

        Map* getMap();
        BattleSetting* getBattleSetting();

    private:
        Map* mapPtr_;
        BattleSetting* battleSettingPtr_;
        //vector<Player*> players_;   // Player not implemented yet - see materials/diagram.webp
        //TurnHandler* turnHandler_;  // TurnHandler not implemented yet - see materials/diagram.webp
};
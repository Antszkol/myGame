#pragma once
#include <vector>
#include <map>

#include "player.hpp"
#include "map.hpp"
#include "mapHandler.hpp"
#include "turnHandler.hpp"

class AIHandler {
    public:
        AIHandler(Map& map, Player* playerPtr, TurnHandler* turnHandlerPtr, MapHandler* mapHandlerPtr);

        void executeTurn();
        std::map<Tile*, int> getDistanceToEnemy(Tile* tilePtr, int range);

    private:
        void waitMs(int milliseconds);

        Player* playerPtr_;
        TurnHandler* turnHandlerPtr_;
        MapHandler* mapHandlerPtr_;
        Map& map_;
};
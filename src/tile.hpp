#pragma once
#include <string>
#include <utility>
#include <vector>

#include "unit.hpp"
#include "tileWidget.hpp"

using namespace std;

class Tile{
    public:
        Tile(pair<int, int> pair, int tileType);

        bool isPassable();
        bool isOccupied();
        bool isWithinDeploymentZone(Player* playerPtr);
        void setIndex(pair<int, int> index);

        pair<int, int> getTileIndex();

        int getTileType() const;
        int getSpeedImpact() const;
        Unit* getOccupant() const;
        void setTileType(int tileType);
        void setOccupation(Unit* occupant);
        void setTileWidget(TileWidget* tileWidgetPtr);
        void setWalkability(bool boolean);
        TileWidget* getTileWidgetPtr();

    private:
        const pair<int, int> tileIndex_;
        const int speedImpact_;
        const int moraleImpact_;
        const int tileType_;

        TileWidget* tileWidgetPtr_;
        Unit* occupant_;
        bool isWalkable_;
};
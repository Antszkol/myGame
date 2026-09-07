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
        bool isWithinDeploymentZone(const Player* playerPtr);

        void setIndex(pair<int, int> index);
        void setTileType(int tileType);
        void setOccupation(Unit* occupant);
        void setTileWidget(TileWidget* tileWidgetPtr);

        pair<int, int> getTileIndex();
        int getTileType() const;
        int getSpeedImpact() const;
        Unit* getOccupant() const;
        TileWidget* getTileWidgetPtr();

    private:
        const pair<int, int> tileIndex_;
        const int speedImpact_;
        const int moraleImpact_;
        const int tileType_;

        TileWidget* tileWidgetPtr_;
        Unit* occupant_;
};
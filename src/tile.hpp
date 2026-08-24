#pragma once
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Tile{
    public:
        Tile(pair<int, int> pair, int tileType);

        bool isPassable();
        void setIndex(pair<int, int> index);

        pair<int, int> getTileIndex();

        int getTileType() const;
        void setTileType(int tileType);
        void setOccupation(bool trueFalse);

    private:
        const pair<int, int> tileIndex_;
        const int speedImpact_;
        const int moraleImpact_;
        const int tileType_;
        bool isOccupied_;
};
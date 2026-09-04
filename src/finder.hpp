#include <queue>
#include <map>
#include "tile.hpp"
#include "map.hpp"
#include "unitStats.hpp"
#include "turnHandler.hpp"

class Finder{
    public:
        Finder(Map& map);

        std::map<Tile*, int> findMovePaths(Tile* startingTile, int speed);
        std::vector<Tile*> FindTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr);

    private:
        Map& map_;
        UnitStats currentUnitStats_;
};
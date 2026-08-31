#include <queue>
#include <map>
#include "tile.hpp"
#include "map.hpp"
#include "unitStats.hpp"

class Finder{
    public:
        Finder(Map& map);

        std::map<Tile*, int> findMovePaths(Tile* startingTile, int speed);
        std::vector<Tile*> FindTargets(Tile* startingTile, UnitStats unitStats);

    private:
        Map& map_;
        Tile* startingTile_;
        UnitStats currentUnitStats_;
};
#pragma once
#include <map>
#include <vector>
#include <utility>

#include "finder.hpp"
#include "tile.hpp"
#include "tileWidget.hpp"
#include "unit.hpp"

using namespace std;

class MapHandler {
    public:
        MapHandler(Map& map);

        void addTileWidget(TileWidget* tileWidgetPtr);

        std::map<Tile*, int> findMovePaths(Tile* startingTile, int speed);
        std::vector<Tile*> findTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr);

        int calculateMorale(Unit* unitPtr, Tile* tilePtr);
        void unsetTileOccupant(TileWidget* tileWidgetPtr);
        void addTileSelection(Tile* tilePtr, int distance);
        void addTargetSelection(Tile* tilePtr);
        void clearTileSelection();
        void clearTargetSelection();
        void clearSelection();
        bool isTileSet(Tile* tilePtr);

        void setUnit(TileWidget* tileWidgetPtr, Unit* unitPtr);
        void setTile(TileWidget* tileWidgetPtr);
        void setUnitSelected(Unit* unitPtr);

        TileWidget* getTileSet();
        Unit* getUnitSelected() const;
        TileWidget* getTileWidgetPtr(pair<int, int> tileIdx) const;
        const std::map<Tile*, int>& getTilesSelectedMap() const;
        const std::vector<Tile*>& getTargetTileVector() const;

    private:
        Finder* finder_;
        std::vector<TileWidget*> tileWidgets_;

        Tile* tileSet_;
        Unit* unitSelected_;
        Map& map_;
        std::map<Tile*, int> tilesSelectedMap_;
        std::vector<Tile*> targetTileVector_;
};

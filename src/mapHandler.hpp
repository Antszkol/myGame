#pragma once
#include <map>
#include <vector>
#include <utility>

#include "finder.hpp"
#include "tile.hpp"
#include "tileWidget.hpp"
#include "unit.hpp"
#include "unitWidget.hpp"

using namespace std;

/// @brief Bridges game logic (Tile/Unit) and the Qt UI layer (TileWidget/UnitWidget): owns the
/// logic<->widget lookup tables and all placement/selection state.
class MapHandler {
    public:
        /// @param map the logic-side map this handler wraps.
        MapHandler(Map& map);

        /// @param tileWidgetPtr widget to register, appended by grid order.
        void addTileWidget(TileWidget* tileWidgetPtr);

        /// @param unitWidgetPtr widget to register for reverse Unit->UnitWidget lookup.
        void addUnitWidget(UnitWidget* unitWidgetPtr);

        /// @param unitPtr unit whose widget should be dropped from the lookup (e.g. on death).
        void removeUnitWidget(Unit* unitPtr);

        /// @param unitPtr unit to look up.
        /// @return the widget representing unitPtr, or nullptr if not found.
        UnitWidget* getUnitWidget(Unit* unitPtr) const;

        /// @brief Wraps Finder::findMovePaths. @see Finder::findMovePaths
        std::map<Tile*, int> findMovePaths(Tile* startingTile, int speed, bool ignoreUnits = false);

        /// @brief Wraps Finder::FindTargets. @see Finder::FindTargets
        std::vector<Tile*> findTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr);

        /// @brief Custom clamping template: constrains value to the [0, 100] range (used for morale).
        /// @tparam T the value's type.
        /// @param value value to clamp.
        /// @return value clamped to [0, 100].
        template<typename T> int clampValue(T value){
            return std::clamp(value, 0, 100);
        }

        /// @param unitPtr unit to compute morale for.
        /// @param tilePtr tile the unit stands on.
        /// @return morale: base 50, +/-8 per adjacent ally/enemy, -20 on mud, clamped to [0, 100].
        int calculateMorale(Unit* unitPtr, Tile* tilePtr);

        /// @param tileWidgetPtr tile to clear the occupant of.
        void unsetTileOccupant(TileWidget* tileWidgetPtr);

        /// @param tilePtr tile to mark as move-reachable.
        /// @param distance BFS distance to that tile, used for highlighting.
        void addTileSelection(Tile* tilePtr, int distance);

        /// @param tilePtr tile to mark as a valid attack target.
        void addTargetSelection(Tile* tilePtr);

        /// @brief Clears the move-reachable tile set.
        void clearTileSelection();

        /// @brief Clears the valid-attack-target tile set.
        void clearTargetSelection();

        /// @brief Clears the currently selected unit and tile.
        void clearSelection();

        /// @param tilePtr tile to check.
        /// @return whether tilePtr is the currently set/selected tile.
        bool isTileSet(Tile* tilePtr);

        /// @param tileWidgetPtr tile to place the unit on.
        /// @param unitPtr unit to place.
        void setUnit(TileWidget* tileWidgetPtr, Unit* unitPtr);

        /// @param tileWidgetPtr tile to mark as the currently set/selected tile.
        void setTile(TileWidget* tileWidgetPtr);

        /// @brief Clears the currently set/selected tile.
        void unsetTile();

        /// @param unitPtr unit to mark as currently selected.
        void setUnitSelected(Unit* unitPtr);

        /// @return the widget for the currently set/selected tile.
        TileWidget* getTileSet();

        /// @return the currently selected unit.
        Unit* getUnitSelected() const;

        /// @param tileIdx (column, row) grid index to look up.
        /// @return the widget for the tile at that index.
        TileWidget* getTileWidgetPtr(pair<int, int> tileIdx) const;

        /// @return every currently move-reachable tile mapped to its BFS distance.
        const std::map<Tile*, int>& getTilesSelectedMap() const;

        /// @return every currently valid attack-target tile.
        const std::vector<Tile*>& getTargetTileVector() const;

    private:
        Finder* finder_;
        std::vector<TileWidget*> tileWidgets_;
        std::vector<UnitWidget*> unitWidgets_;

        Tile* tileSet_;
        Unit* unitSelected_;
        Map& map_;
        std::map<Tile*, int> tilesSelectedMap_;
        std::vector<Tile*> targetTileVector_;
};

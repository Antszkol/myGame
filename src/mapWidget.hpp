#pragma once
#include <QWidget>
#include <QBrush>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <algorithm>

#include "baseScreenWidget.hpp"
#include "map.hpp"
#include "mapHandler.hpp"
#include "tileWidget.hpp"
#include "tileType.hpp"
#include "turnHandler.hpp"

/// @brief QGraphicsView rendering the battle map: owns the TileWidget/UnitWidget scene and
/// handles hover/click input, delegating placement/selection bookkeeping to MapHandler.
class MapWidget : public QGraphicsView {
    Q_OBJECT
    public:
        /// @param argMap the logic-side map to render.
        /// @param turnHandlerPtr turn handler to route move/attack/deploy actions to.
        MapWidget(Map& argMap, TurnHandler* turnHandlerPtr);
        ~MapWidget();

        /// @brief Paints tilePtr's tile as the currently selected unit's own tile.
        /// @param tileWidgetPtr tile widget to highlight.
        void selectTile(TileWidget* tileWidgetPtr);

        /// @brief Restores tileWidgetPtr's tile to its normal terrain color.
        /// @param tileWidgetPtr tile widget to restore.
        void unSelectTile(TileWidget* tileWidgetPtr);

        /// @brief Click-handling entry point for hovering over a tile; behavior depends on the
        /// current ActionMode (preview move/attack/deploy).
        /// @param tileWidgetPtr the hovered tile.
        void onTileHovered(TileWidget* tileWidgetPtr);

        /// @brief Reverts hover-preview effects from onTileHovered.
        /// @param tileWidgetPtr the tile the pointer left.
        void onTileLeft(TileWidget* tileWidgetPtr);

        /// @brief Click-handling entry point for clicking a tile; drives the two-click
        /// select-then-confirm flow for move/attack/deploy depending on the current ActionMode.
        /// @param tileWidgetPtr the clicked tile.
        void onTileClicked(TileWidget* tileWidgetPtr);

        /// @brief Repaints every currently move-reachable tile back to its normal color and
        /// clears that selection in MapHandler.
        void removeTileSelection();

        /// @brief Repaints every currently valid attack-target tile back to its normal color and
        /// clears that selection in MapHandler.
        void removeTargetSelection();

        /// @brief Combines removeTileSelection, removeTargetSelection and unSelectTile for a full
        /// selection reset (e.g. at the end of a turn).
        void removeAllSelection();

        /// @return the logic-side map being rendered.
        Map* getMapPtr() const;

        /// @return the MapHandler backing this view.
        MapHandler* getMapHandlerPtr() const;

        QPainter painter_;
        QBrush brush_;

    private:
        /// @brief Paints a single tile's base terrain sprite/color.
        void paintTile(QPainter* painter, TileWidget* tileWidgetPtr);

        /// @brief Resets a tile's brush to its terrain's base sprite/color.
        void restoreTileColor(Tile* tilePtr);

        /// @brief Picks the highlight brush for a tile's own-selected terrain variant.
        QBrush getSelectedBrush(Tile* tilePtr);

        MapHandler* mapHandler_;
        QGraphicsScene* scene_;
        Map* map_;
        TurnHandler* turnHandlerPtr_;
};

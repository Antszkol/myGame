#pragma once
#include <QGraphicsRectItem>
#include <utility>

class MapWidget;
class Tile;

/// @brief Graphical representation of a single Tile; forwards hover/click events to MapWidget.
class TileWidget : public QGraphicsRectItem {
    public:
        /// @param tilePtr the logic-side Tile this widget represents.
        /// @param mapWidgetPtr owning map view, used to route hover/click callbacks.
        TileWidget(Tile* tilePtr, MapWidget* mapWidgetPtr);

        /// @return the logic-side Tile this widget represents.
        Tile* getTilePtr();

        /// @return the map view this tile belongs to.
        MapWidget* getMapWidgetPtr();

    private:
        Tile* tilePtr_;
        MapWidget* mapWidgetPtr_;

    protected:
        /// @brief Forwards to MapWidget::onTileHovered.
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        /// @brief Forwards to MapWidget::onTileLeft.
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
        /// @brief Forwards to MapWidget::onTileClicked.
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
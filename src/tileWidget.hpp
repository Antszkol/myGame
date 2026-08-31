#pragma once
#include <QGraphicsRectItem>
#include <utility>

class MapWidget;
class Tile;

class TileWidget : public QGraphicsRectItem {
    public:
        TileWidget(Tile* tilePtr, MapWidget* mapWidgetPtr);
        Tile* getTilePtr();
        MapWidget* getMapWidgetPtr();

    private:
        Tile* tilePtr_;
        MapWidget* mapWidgetPtr_;

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
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

class MapWidget : public QGraphicsView {
    Q_OBJECT
    public:
        MapWidget(Map& argMap, TurnHandler* turnHandlerPtr);
        ~MapWidget();

        void selectTile(TileWidget* tileWidgetPtr);
        void unSelectTile(TileWidget* tileWidgetPtr);

        void onTileHovered(TileWidget* tileWidgetPtr);
        void onTileLeft(TileWidget* tileWidgetPtr);
        void onTileClicked(TileWidget* tileWidgetPtr);

        void removeTileSelection();
        void removeTargetSelection();
        void removeAllSelection();

        Map* getMapPtr() const;
        MapHandler* getMapHandlerPtr() const;

        QPainter painter_;
        QBrush brush_;

    private:
        void paintTile(QPainter* painter, TileWidget* tileWidgetPtr);
        void restoreTileColor(Tile* tilePtr);
        QBrush getSelectedBrush(Tile* tilePtr);

        MapHandler* mapHandler_;
        QGraphicsScene* scene_;
        Map* map_;
        TurnHandler* turnHandlerPtr_;
};

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
#include "finder.hpp"
#include "tileWidget.hpp"
#include "tileType.hpp"
#include "turnHandler.hpp"

class MapWidget : public QGraphicsView {
    Q_OBJECT
    public:
        MapWidget(Map& argMap, TurnHandler* turnHandlerPtr);
        ~MapWidget();

        QPainter painter_;
        QBrush brush_;

        TileWidget* getTileWidgetPtr(pair<int, int> tileIdx) const;
        Map* getMapPtr() const;
        void onTileHovered(TileWidget* tileWidgetPtr);
        void onTileLeft(TileWidget* tileWidgetPtr);
        void onTileClicked(TileWidget* tileWidgetPtr);

        void unsetUnit(TileWidget* tileWidgetPtr);
        void setUnit(TileWidget* tileWidgetPtr, Unit* unitPtr);

        void addTileSelection(Tile* tilePtr, int distance);
        void removeTileSelection();

        void setTile(TileWidget* tileWidgetPtr);
        bool isTileset();

    private:
        Finder* finder;
        QGraphicsScene* scene;
        Map* map;
        TurnHandler* turnHandlerPtr_;
        std::vector<TileWidget*> tileWidgets_;

        bool isTileset_;
        Tile* tileSet_;
        Unit* unitSelected_;
        std::map<Tile*, int> tilesSelectedMap_;
        

        void paintTile(QPainter* painter, TileWidget* tile);
};
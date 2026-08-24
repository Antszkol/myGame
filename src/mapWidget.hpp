#pragma once
#include <QWidget>
#include <QBrush>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>

#include "baseScreenWidget.hpp"
#include "map.hpp"
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

        TileWidget* getTileWidgetPtr(pair<int, int> tileIdx);
        void onTileHovered(TileWidget* tileWidgetPtr);
        void onTileLeft(TileWidget* tileWidgetPtr);
        void onTileClicked(TileWidget* tileWidgetPtr);

    private:
        QGraphicsScene* scene;
        Map* map;
        TurnHandler* turnHandlerPtr_;
        std::vector<TileWidget*> tileWidgets_;

        void loadMap();
        void paintTile(QPainter* painter, TileWidget* tile);
};
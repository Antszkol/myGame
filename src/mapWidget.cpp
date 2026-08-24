#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include "mapWidget.hpp"
#include "tileWidget.hpp"
#include "map.hpp"
#include "tile.hpp"
#include "tileType.hpp"

MapWidget::MapWidget(Map& argMap, TurnHandler* turnHandlerPtr){
    this->map = &argMap;
    scene = new QGraphicsScene(this);

    // mapWidget musi, dla tworzenia tiles, miec wskaznik do tile (dla tileWidget)
    for(int i = 0; i < argMap.getMapSize().first * argMap.getMapSize().second; i++){
        int x = i % argMap.getMapSize().first;
        int y = i / argMap.getMapSize().first;
        this->turnHandlerPtr_ = turnHandlerPtr;
        TileWidget* tileWidgetPtr = new TileWidget(this->map->getTileByIndex({x, y}), this);
        this->paintTile(&(this->painter_), tileWidgetPtr);
        scene->addItem(tileWidgetPtr);
        this->tileWidgets_.push_back(tileWidgetPtr);
    }
    this->setScene(scene);
}

MapWidget::~MapWidget(){}

void MapWidget::paintTile(QPainter* painter, TileWidget* tileWidgetPtr){
    Tile* tilePtr = tileWidgetPtr->getTilePtr();

    if(tilePtr->getTileType() == grass){
        tileWidgetPtr->setBrush(QBrush(QColor(64, 255, 64, 255), Qt::CrossPattern));
        tileWidgetPtr->update();    
    }
    if(tilePtr->getTileType() == mud){
        tileWidgetPtr->setBrush(QBrush(QColor(255, 255, 128, 255), Qt::Dense1Pattern));
        tileWidgetPtr->update();    
    }
    if(tilePtr->getTileType() == water){
        tileWidgetPtr->setBrush(QBrush(QColor(64, 64, 255, 255), Qt::Dense3Pattern));
        tileWidgetPtr->update();    
    }
}

TileWidget* MapWidget::getTileWidgetPtr(pair<int, int> tileIdx){
    return this->tileWidgets_[(tileIdx.first * 8) + tileIdx.second];
}

void MapWidget::onTileHovered(TileWidget* tileWidgetPtr){
    tileWidgetPtr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::RecruitUnit){
        if(tileWidgetPtr->getTilePtr()->isPassable()){
            tileWidgetPtr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        }
        else{
            tileWidgetPtr->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        }
    }
}

void MapWidget::onTileLeft(TileWidget* tileWidgetPtr){
    if(tileWidgetPtr->getTilePtr()->getTileType() == grass){
        tileWidgetPtr->setBrush(QBrush(QColor(64, 255, 64, 255), Qt::CrossPattern));
    }
    if(tileWidgetPtr->getTilePtr()->getTileType() == mud){
        tileWidgetPtr->setBrush(QBrush(QColor(255, 255, 128, 255), Qt::Dense1Pattern));
    }
    if(tileWidgetPtr->getTilePtr()->getTileType() == water){
        tileWidgetPtr->setBrush(QBrush(QColor(64, 64, 255, 255), Qt::Dense3Pattern));
    }
}

void MapWidget::onTileClicked(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::RecruitUnit){
        if(tileWidgetPtr->getTilePtr()->isPassable()){
            this->turnHandlerPtr_->confirmUnitDeployment(tileWidgetPtr);
        }
    }
}
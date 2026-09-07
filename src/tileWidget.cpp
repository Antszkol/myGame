#include "tileWidget.hpp"
#include "mapWidget.hpp"
#include "tile.hpp"

TileWidget::TileWidget(Tile* tilePtr, MapWidget* mapWidgetPtr) : QGraphicsRectItem(){
    setAcceptHoverEvents(true);
    this->tilePtr_ = tilePtr;
    this->mapWidgetPtr_ = mapWidgetPtr;
    int scaleFactor = 80;
    pair<int, int> tileIndex = this->tilePtr_->getTileIndex();
    this->setRect(0, 0, scaleFactor, scaleFactor);
    this->setPos(tileIndex.first*scaleFactor, tileIndex.second*scaleFactor);
}

void TileWidget::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if(this->mapWidgetPtr_){
        mapWidgetPtr_->onTileHovered(this);
    }
    QGraphicsRectItem::hoverEnterEvent(event);
}

void TileWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    if(this->mapWidgetPtr_){
        mapWidgetPtr_->onTileLeft(this);
    }
    QGraphicsRectItem::hoverLeaveEvent(event);
}

void TileWidget::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(mapWidgetPtr_){
        this->mapWidgetPtr_->onTileClicked(this);
    }
    QGraphicsRectItem::mousePressEvent(event);
}

Tile* TileWidget::getTilePtr(){
    return this->tilePtr_;
};
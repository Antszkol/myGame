#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include "mapWidget.hpp"
#include "tileWidget.hpp"
#include "map.hpp"
#include "tile.hpp"
#include "tileType.hpp"

MapWidget::MapWidget(Map& argMap, TurnHandler* turnHandlerPtr){
    this->map_ = &argMap;
    scene_ = new QGraphicsScene(this);
    this->turnHandlerPtr_ = turnHandlerPtr;
    this->mapHandler_ = new MapHandler(*(this->map_));

    for(int i = 0; i < argMap.getMapSize().first * argMap.getMapSize().second; i++){
        int x = i % argMap.getMapSize().first;
        int y = i / argMap.getMapSize().first;
        TileWidget* tileWidgetPtr = new TileWidget(this->map_->getTileByIndex({x, y}), this);
        tileWidgetPtr->getTilePtr()->setTileWidget(tileWidgetPtr);
        this->paintTile(&(this->painter_), tileWidgetPtr);
        scene_->addItem(tileWidgetPtr);
        this->mapHandler_->addTileWidget(tileWidgetPtr);
    }
    this->setScene(scene_);
}

MapWidget::~MapWidget(){}

void MapWidget::paintTile(QPainter* painter, TileWidget* tileWidgetPtr){
    this->restoreTileColor(tileWidgetPtr->getTilePtr());
}

void MapWidget::restoreTileColor(Tile* tilePtr){
    if(tilePtr->getTileType() == grass){
        tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 255, 64, 255), Qt::CrossPattern));
    }
    if(tilePtr->getTileType() == mud){
        tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(255, 255, 128, 255), Qt::Dense1Pattern));
    }
    if(tilePtr->getTileType() == water){
        tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 64, 255, 255), Qt::Dense3Pattern));
    }
    tilePtr->getTileWidgetPtr()->update();
    return;
}

void MapWidget::onTileHovered(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit && this->mapHandler_->getUnitSelected() != nullptr){
        return;
    }
    else if(this->turnHandlerPtr_->getActionMode() == ActionMode::RecruitUnit){
        if(tileWidgetPtr->getTilePtr()->isPassable()
        && tileWidgetPtr->getTilePtr()->isWithinDeploymentZone(this->turnHandlerPtr_->getCurrentPlayerPtr())){
            tileWidgetPtr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
        }
        else{
            tileWidgetPtr->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        }
    }
    else if(this->turnHandlerPtr_->getActionMode() == ActionMode::None){
        tileWidgetPtr->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    }
}

void MapWidget::onTileLeft(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit && this->mapHandler_->getUnitSelected() != nullptr){
        return;
    }
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::AttackUnit && this->mapHandler_->getUnitSelected() != nullptr){
        return;
    }
    else {
        this->restoreTileColor(tileWidgetPtr->getTilePtr());
    }
    return;
}

void MapWidget::onTileClicked(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::RecruitUnit){
        if(tileWidgetPtr->getTilePtr()->isPassable() && tileWidgetPtr->getTilePtr()->isWithinDeploymentZone(this->turnHandlerPtr_->getCurrentPlayerPtr())){
            this->turnHandlerPtr_->confirmUnitDeployment(tileWidgetPtr);
        }
    }

    // MOVE UNIT
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit){
        // MoveUnit : second click (unit selected)
        if(this->mapHandler_->getUnitSelected() != nullptr && this->mapHandler_->isTileSet(tileWidgetPtr->getTilePtr())){
            this->removeTileSelection();
            this->mapHandler_->clearSelection();
        }
        else if(this->mapHandler_->getUnitSelected() != nullptr && tileWidgetPtr->getTilePtr()->isPassable() && this->mapHandler_->getTilesSelectedMap().contains(tileWidgetPtr->getTilePtr())){
            this->mapHandler_->getUnitSelected()->subtractSpeed(this->mapHandler_->getTilesSelectedMap().at(tileWidgetPtr->getTilePtr()));
            this->turnHandlerPtr_->setActionMode(ActionMode::None);
            this->turnHandlerPtr_->moveUnit(this->mapHandler_->getTileSet(), tileWidgetPtr);
            this->removeTileSelection();
            this->mapHandler_->clearSelection();
        }

        // MoveUnit : first click (unit not yet selected)
        else if(tileWidgetPtr->getTilePtr()->getOccupant()
                && this->mapHandler_->getUnitSelected() == nullptr
                && tileWidgetPtr->getTilePtr()->getOccupant()->getOwnerPtr() == this->turnHandlerPtr_->getCurrentPlayerPtr()
                && tileWidgetPtr->getTilePtr()->getOccupant()->getRemainingSpeed() > 0){
            this->mapHandler_->setTile(tileWidgetPtr);
            this->mapHandler_->setUnitSelected(tileWidgetPtr->getTilePtr()->getOccupant());
            std::map<Tile*, int> distMap = this->mapHandler_->findMovePaths(tileWidgetPtr->getTilePtr(), this->mapHandler_->getUnitSelected()->getRemainingSpeed());
            for(auto const& [tilePtr, distance] : distMap){
                if((distance <= this->mapHandler_->getUnitSelected()->getRemainingSpeed()) &&
                    tilePtr->getTileWidgetPtr() != tileWidgetPtr){
                    if(tilePtr->isPassable()){
                        this->mapHandler_->addTileSelection(tilePtr, distance);
                        tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::green, Qt::SolidPattern));
                    }
                    if(tilePtr->isPassable() == false){
                        this->mapHandler_->addTileSelection(tilePtr, distance);
                        tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    }
                }
            }
        }
    }

    // ATTACK UNIT
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::AttackUnit){
        // second click
        if(this->mapHandler_->getUnitSelected() != nullptr && this->mapHandler_->isTileSet(tileWidgetPtr->getTilePtr())){
            this->removeTargetSelection();
            this->mapHandler_->clearSelection();
        }
        else if(this->mapHandler_->getUnitSelected() != nullptr
            && std::find(this->mapHandler_->getTargetTileVector().begin(), this->mapHandler_->getTargetTileVector().end(), tileWidgetPtr->getTilePtr()) != this->mapHandler_->getTargetTileVector().end()){
            this->turnHandlerPtr_->setActionMode(ActionMode::None);
            this->turnHandlerPtr_->attackUnit(this->mapHandler_->getTileSet(), tileWidgetPtr);
            this->removeTargetSelection();
            this->mapHandler_->clearSelection();
        }
        // first click
        else if(tileWidgetPtr->getTilePtr()->getOccupant()
                && this->mapHandler_->getUnitSelected() == nullptr
                && tileWidgetPtr->getTilePtr()->getOccupant()->getOwnerPtr() == this->turnHandlerPtr_->getCurrentPlayerPtr()
                && !tileWidgetPtr->getTilePtr()->getOccupant()->hasAttacked()){
            this->mapHandler_->setTile(tileWidgetPtr);
            this->mapHandler_->setUnitSelected(tileWidgetPtr->getTilePtr()->getOccupant());
            std::vector<Tile*> targetTileVector = this->mapHandler_->findTargets(tileWidgetPtr->getTilePtr(), this->mapHandler_->getUnitSelected()->getUnitStats().range_, this->turnHandlerPtr_->getCurrentPlayerPtr());
            for(auto const& tilePtr : targetTileVector){
                this->mapHandler_->addTargetSelection(tilePtr);
                tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            }
        }
    }
}

void MapWidget::removeTileSelection(){
    for(const auto& [tilePtr, distance] : this->mapHandler_->getTilesSelectedMap()){
        this->restoreTileColor(tilePtr);
    }
    this->mapHandler_->clearTileSelection();
    return;
}

void MapWidget::removeTargetSelection(){
    for(const auto& tilePtr : this->mapHandler_->getTargetTileVector()){
        this->restoreTileColor(tilePtr);
    }
    this->mapHandler_->clearTargetSelection();
    return;
}

void MapWidget::removeAllSelection(){
    this->removeTileSelection();
    this->removeTargetSelection();
    this->mapHandler_->clearSelection();
}

Map* MapWidget::getMapPtr() const {
    return this->map_;
}

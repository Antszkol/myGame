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
    this->finder = new Finder(*(this->getMapPtr()));

    // mapWidget musi, dla tworzenia tiles, miec wskaznik do tile (dla tileWidget)
    for(int i = 0; i < argMap.getMapSize().first * argMap.getMapSize().second; i++){
        int x = i % argMap.getMapSize().first;
        int y = i / argMap.getMapSize().first;
        this->turnHandlerPtr_ = turnHandlerPtr;
        TileWidget* tileWidgetPtr = new TileWidget(this->map->getTileByIndex({x, y}), this);
        tileWidgetPtr->getTilePtr()->setTileWidget(tileWidgetPtr);
        this->paintTile(&(this->painter_), tileWidgetPtr);
        scene->addItem(tileWidgetPtr);
        this->tileWidgets_.push_back(tileWidgetPtr);
        this->unitSelected_ = nullptr;
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
        tileWidgetPtr->getTilePtr()->setWalkability(false);
        tileWidgetPtr->update();    
    }
}

TileWidget* MapWidget::getTileWidgetPtr(pair<int, int> tileIdx) const {
    return this->tileWidgets_[(tileIdx.first * 8) + tileIdx.second];
}

void MapWidget::onTileHovered(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit && this->unitSelected_ != nullptr){
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
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit && this->unitSelected_ != nullptr){
        return;
    }
    else {
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
    return;
}

Map* MapWidget::getMapPtr() const {
    return this->map;
}

void MapWidget::onTileClicked(TileWidget* tileWidgetPtr){
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::RecruitUnit){
        if(tileWidgetPtr->getTilePtr()->isPassable()){
            this->turnHandlerPtr_->confirmUnitDeployment(tileWidgetPtr);
        }
    }

    // MOVE UNIT
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::MoveUnit){
        // MoveUnit : second click (unitSelected_ set)
        if(this->unitSelected_ != nullptr && tileWidgetPtr->getTilePtr() == tileSet_){
            this->removeTileSelection();
            this->unitSelected_ = nullptr;
            this->tileSet_ = nullptr;
        }
        else if(this->unitSelected_ != nullptr && tileWidgetPtr->getTilePtr()->isPassable() && this->tilesSelectedMap_.contains(tileWidgetPtr->getTilePtr())){
            this->unitSelected_->subtractSpeed(this->tilesSelectedMap_.at(tileWidgetPtr->getTilePtr()));
            this->turnHandlerPtr_->setActionMode(ActionMode::None);
            this->turnHandlerPtr_->moveUnit(this->tileSet_->getTileWidgetPtr(), tileWidgetPtr);
            this->removeTileSelection();
            this->unitSelected_ = nullptr;
            this->tileSet_ = nullptr;
        }

        // MoveUnit : first click (unitSelected_ unset)
        else if(tileWidgetPtr->getTilePtr()->getOccupant() 
                && this->unitSelected_ == nullptr 
                && tileWidgetPtr->getTilePtr()->getOccupant()->getRemainingSpeed() > 0){
            this->setTile(tileWidgetPtr);
            this->unitSelected_ = tileWidgetPtr->getTilePtr()->getOccupant();
            std::map<Tile*, int> distMap = this->finder->findMovePaths(tileWidgetPtr->getTilePtr(), this->unitSelected_->getRemainingSpeed());
            for(auto const& [tilePtr, distance] : distMap){
                if((distance <= this->unitSelected_->getRemainingSpeed()) &&
                    tilePtr->getTileWidgetPtr() != tileWidgetPtr){
                    if(tilePtr->isPassable()){
                        this->addTileSelection(tilePtr, distance);
                        tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::green, Qt::SolidPattern));
                    }
                    if(tilePtr->isPassable() == false){
                        this->addTileSelection(tilePtr, distance);
                        tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::red, Qt::SolidPattern));
                    }
                }
            }
        }
    }

    // ATTACK UNIT
    if(this->turnHandlerPtr_->getActionMode() == ActionMode::AttackUnit){
        // second click
        if(this->unitSelected_ != nullptr && tileWidgetPtr->getTilePtr() == tileSet_){
            this->removeTargetSelection();
            this->unitSelected_ = nullptr;
            this->tileSet_ = nullptr;
        }
        else if(this->unitSelected_ != nullptr 
            && std::find(this->targetTileVector_.begin(), this->targetTileVector_.end(), tileWidgetPtr->getTilePtr()) != this->targetTileVector_.end()){
            this->turnHandlerPtr_->setActionMode(ActionMode::None);
            this->turnHandlerPtr_->attackUnit(this->tileSet_->getTileWidgetPtr(), tileWidgetPtr);
            this->removeTargetSelection();
            this->unitSelected_ = nullptr;
            this->tileSet_ = nullptr;
        }
        // first click
        else if(tileWidgetPtr->getTilePtr()->getOccupant() && this->unitSelected_ == nullptr){
            this->setTile(tileWidgetPtr);
            this->unitSelected_ = tileWidgetPtr->getTilePtr()->getOccupant();
            std::vector<Tile*> targetTileVector = this->finder->FindTargets(tileWidgetPtr->getTilePtr(), this->unitSelected_->getUnitStats().range_, this->turnHandlerPtr_->getCurrentPlayerPtr());
            for(auto const& tilePtr : targetTileVector){
                this->addTargetSelection(tilePtr);
                tilePtr->getTileWidgetPtr()->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
            }
        }
    }
}

void MapWidget::removeTileSelection(){
    for(const auto& [tilePtr, distance] : this->tilesSelectedMap_){
        if(tilePtr->getTileType() == grass){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 255, 64, 255), Qt::CrossPattern));
        }
        if(tilePtr->getTileType() == mud){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(255, 255, 128, 255), Qt::Dense1Pattern));
        }
        if(tilePtr->getTileType() == water){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 64, 255, 255), Qt::Dense3Pattern));
        }
    }
    this->tilesSelectedMap_.clear();

    return;
}

void MapWidget::removeTargetSelection(){
    for(const auto& tilePtr : this->targetTileVector_){
        if(tilePtr->getTileType() == grass){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 255, 64, 255), Qt::CrossPattern));
        }
        if(tilePtr->getTileType() == mud){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(255, 255, 128, 255), Qt::Dense1Pattern));
        }
        if(tilePtr->getTileType() == water){
            tilePtr->getTileWidgetPtr()->setBrush(QBrush(QColor(64, 64, 255, 255), Qt::Dense3Pattern));
        }
    }
    this->targetTileVector_.clear();

    return;
}

void MapWidget::addTileSelection(Tile* tilePtr, int distance){
    this->tilesSelectedMap_[tilePtr] = distance;
    return;
}

void MapWidget::addTargetSelection(Tile* tilePtr){
    this->targetTileVector_.push_back(tilePtr);
    return;
}

void MapWidget::unsetUnit(TileWidget* tileWidgetPtr){
    tileWidgetPtr->getTilePtr()->setOccupation(nullptr);
    return;
}

void MapWidget::setTile(TileWidget* tileWidgetPtr){
    this->tileSet_ = tileWidgetPtr->getTilePtr();
    return;
}
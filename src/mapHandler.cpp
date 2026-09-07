#include "mapHandler.hpp"
#include "map.hpp"

MapHandler::MapHandler(Map& map){
    this->finder_ = new Finder(map);
    this->tileSet_ = nullptr;
    this->unitSelected_ = nullptr;
}

void MapHandler::addTileWidget(TileWidget* tileWidgetPtr){
    this->tileWidgets_.push_back(tileWidgetPtr);
    return;
}

std::map<Tile*, int> MapHandler::findMovePaths(Tile* startingTile, int speed){
    return this->finder_->findMovePaths(startingTile, speed);
}

std::vector<Tile*> MapHandler::findTargets(Tile* startingTilePtr, int range, Player* currentPlayerPtr){
    return this->finder_->FindTargets(startingTilePtr, range, currentPlayerPtr);
}

void MapHandler::unsetUnit(TileWidget* tileWidgetPtr){
    tileWidgetPtr->getTilePtr()->setOccupation(nullptr);
    return;
}

void MapHandler::addTileSelection(Tile* tilePtr, int distance){
    this->tilesSelectedMap_[tilePtr] = distance;
    return;
}

void MapHandler::addTargetSelection(Tile* tilePtr){
    this->targetTileVector_.push_back(tilePtr);
    return;
}

void MapHandler::clearTileSelection(){
    this->tilesSelectedMap_.clear();
    return;
}

void MapHandler::clearTargetSelection(){
    this->targetTileVector_.clear();
    return;
}

void MapHandler::clearSelection(){
    this->unitSelected_ = nullptr;
    this->tileSet_ = nullptr;
    return;
}

bool MapHandler::isTileSet(Tile* tilePtr){
    return this->tileSet_ == tilePtr;
}

void MapHandler::setUnit(TileWidget* tileWidgetPtr, Unit* unitPtr){
    tileWidgetPtr->getTilePtr()->setOccupation(unitPtr);
    return;
}

void MapHandler::setTile(TileWidget* tileWidgetPtr){
    this->tileSet_ = tileWidgetPtr->getTilePtr();
    return;
}

void MapHandler::setUnitSelected(Unit* unitPtr){
    this->unitSelected_ = unitPtr;
    return;
}

TileWidget* MapHandler::getTileSet(){
    return this->tileSet_->getTileWidgetPtr();
}

Unit* MapHandler::getUnitSelected() const {
    return this->unitSelected_;
}

TileWidget* MapHandler::getTileWidgetPtr(pair<int, int> tileIdx) const {
    return this->tileWidgets_[(tileIdx.first * 8) + tileIdx.second];
}

const std::map<Tile*, int>& MapHandler::getTilesSelectedMap() const {
    return this->tilesSelectedMap_;
}

const std::vector<Tile*>& MapHandler::getTargetTileVector() const {
    return this->targetTileVector_;
}

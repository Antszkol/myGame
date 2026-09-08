#include "aiHandler.hpp"

#include <QEventLoop>
#include <QTimer>

AIHandler::AIHandler(Map& map, Player* playerPtr, TurnHandler* turnHandlerPtr, MapHandler* mapHandlerPtr) : map_(map) {
    this->playerPtr_ = playerPtr;
    this->turnHandlerPtr_ = turnHandlerPtr;
    this->mapHandlerPtr_ = mapHandlerPtr;
    return;
};

void AIHandler::waitMs(int milliseconds){
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
    return;
}

void AIHandler::executeTurn(){

    // calculate distance to enemy's deployment zone:
        // get deployment zone's closest tiles
            // create a vector for arrays[3] (tile, tile, distance)
            // take a random tile from enemy deployment zone
            // calculate distance between any ai's deployment zone tile
            // do it for every ai tile, update the map if distance is smaller
            // deploy certain amount of units on the tiles that are tthe closest

    std::map<Tile*, int> mainDistMap;
    std::vector<Tile*> enemyTileVector;
    std::vector<Tile*> myTileVector;

    for(const auto& tilePointer : this->map_.getMapTiles()){
        // if tile belongs to enemy's deployment zone
        if(tilePointer->isWithinDeploymentZone(turnHandlerPtr_->getNotCurrentPlayerPtr())){
            enemyTileVector.push_back(tilePointer);
        }
        if(tilePointer->isWithinDeploymentZone(turnHandlerPtr_->getCurrentPlayerPtr())){
            myTileVector.push_back(tilePointer);
        }
    }

    for(const auto& tilePointer : myTileVector){
        mainDistMap[tilePointer] = 10000;
    }

    std::map<Tile*, int> tempDistMap;
    tempDistMap.clear();

    for(const auto& tilePointer : enemyTileVector){
        // returns pair<myTile*, distance to enemy zone> — ignoreUnits: this is a distance
        // heuristic, not real movement, so blocking units shouldn't stop the search
        tempDistMap = mapHandlerPtr_->findMovePaths(tilePointer, 10000, true);
 
        // for each of my tiles
        for(const auto& tempTilePointer : myTileVector){
            // if distance at the distmap is bigger than distance during this iteration
            if(!tempDistMap.contains(tempTilePointer)) continue;

            if(mainDistMap.at(tempTilePointer) > tempDistMap.at(tempTilePointer)){
                mainDistMap.at(tempTilePointer) = tempDistMap.at(tempTilePointer);
            }
        }
    }

    int lowestDist = 10000;
    for(const auto& pair : mainDistMap){
        if(lowestDist > pair.second){
            lowestDist = pair.second;
        }
    }

    std::vector<Tile*> closeTiles;

    for(const auto& pair : mainDistMap){
        if(lowestDist == pair.second){
            closeTiles.push_back(pair.first);
        }
    }

    for(const auto& tilePointer : closeTiles){
        this->turnHandlerPtr_->recruitUnitSlot(UnitType::footman);
        this->turnHandlerPtr_->confirmUnitDeployment(this->mapHandlerPtr_->getTileWidgetPtr(tilePointer->getTileIndex()));
        this->waitMs(800);
    }

    // for each unit:
    //    if any available target:
    //       attack enemy()
    //
    //    for each tile from mapHandlerPtr_->findMovePaths():
    //       calculate distance to deployment zone
    //       move to the tile that's the closest
    //
    //    // again:     
    //    if any available target:
    //       attack enemy()

    for(const auto& unitPointer : this->playerPtr_->getUnits()){
        if(!unitPointer->hasAttacked()){
            std::vector<Tile*> targetTiles = this->mapHandlerPtr_->findTargets(
            this->mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr()->getTilePtr(),
            unitPointer->getUnitStats().range_,
            this->playerPtr_);

            if(!targetTiles.empty()){
                this->turnHandlerPtr_->attackUnit(
                this->mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr(),
                this->mapHandlerPtr_->getTileWidgetPtr(targetTiles[0]->getTileIndex()));
                this->waitMs(800);
            }
        }
    }

    std::map<Tile*, int> moveDistMap;

    // trzeba tutaj wybrac tileWidget ktory jest najblizej
    for(const auto& unitPointer : this->playerPtr_->getUnits()){
        moveDistMap = this->getDistanceToEnemy(mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr()->getTilePtr(), unitPointer->getRemainingSpeed());

        int lowestDist = 10000;
        for(const auto& pair : moveDistMap){
            if(lowestDist > pair.second){
                lowestDist = pair.second;
            }
        }

        Tile* destTilePtr = nullptr;

        for(const auto& [tilePointer, distance] : moveDistMap){
            if(distance == lowestDist){
                destTilePtr = tilePointer;
                continue;
            }
        }

        if(destTilePtr != nullptr){
            turnHandlerPtr_->moveUnitSlot();
            turnHandlerPtr_->moveUnit(
                mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr(),
                mapHandlerPtr_->getTileWidgetPtr(destTilePtr->getTileIndex()));
            this->waitMs(800);
        }
    }

    //calculate distance to enemy deployment zone

    for(const auto& unitPointer : this->playerPtr_->getUnits()){
        if(!unitPointer->hasAttacked()){
            std::vector<Tile*> targetTiles = this->mapHandlerPtr_->findTargets(
            this->mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr()->getTilePtr(),
            unitPointer->getUnitStats().range_,
            this->playerPtr_);

            if(!targetTiles.empty()){
                this->turnHandlerPtr_->attackUnit(
                this->mapHandlerPtr_->getUnitWidget(unitPointer)->getTileWidgetPtr(),
                this->mapHandlerPtr_->getTileWidgetPtr(targetTiles[0]->getTileIndex()));
                this->waitMs(800);
            }
        }
    }

    this->turnHandlerPtr_->endTurnSlot();

    return;
}

std::map<Tile*, int> AIHandler::getDistanceToEnemy(Tile* tilePtr, int range){
    std::vector<Tile*> enemyTileVector;

    // zdobac tiles w zasiegu jednostki
    // dopiero dla nich policz distance do enemy
    // wybierz ta z zasiegu jednostki o najmniejszym distance

    for(const auto& tilePointer : this->map_.getMapTiles()){
        // if tile belongs to enemy's deployment zone
        if(tilePointer->isWithinDeploymentZone(turnHandlerPtr_->getNotCurrentPlayerPtr())){
            enemyTileVector.push_back(tilePointer);
        }
    }

    std::map<Tile*, int> unitRangeMap = this->mapHandlerPtr_->findMovePaths(tilePtr, range);
    std::map<Tile*, int> finalDistMap;

    // policz distance tile z unitRangeMap do enemy deploymentzone i wtedy dorzuc do final distMap

    for(const auto& [tilePointerrr, distance] : unitRangeMap){
        if(distance > range){
            continue;
        }
        
        std::map<Tile*, int> tempDistMap = this->mapHandlerPtr_->findMovePaths(tilePointerrr, 10000, true);
        int lowestDist = 10000;

        for(const auto& [tilePointer, distance] : tempDistMap){
            if(tilePointer->isWithinDeploymentZone(this->turnHandlerPtr_->getNotCurrentPlayerPtr()) && distance <= lowestDist){
                lowestDist = distance;
            }
        }

        for(const auto& [tilePointer, distance] : tempDistMap){
            if(tilePointer->isWithinDeploymentZone(this->turnHandlerPtr_->getNotCurrentPlayerPtr()) && distance <= lowestDist){
                finalDistMap[tilePointerrr] = distance;
                continue;
            }
        }
    }

    return finalDistMap;
}
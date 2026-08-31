#include "unitWidget.hpp"
#include "unit.hpp"

UnitWidget::UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr){
    int scaleFactor = 40;
    this->setRect(20, 20, scaleFactor, scaleFactor);
    if(unitType == footman){
        this->setBrush(QBrush(Qt::red, Qt::Dense1Pattern));
    }
    else if(unitType == archer){
        this->setBrush(QBrush(Qt::yellow, Qt::Dense1Pattern));
    }
    this->setCurrentTileWidget(destinationTileWidgetPtr);
}

void UnitWidget::setUnitPtr(Unit* unitPtr){
    this->unitPtr_ = unitPtr;
    return;
}

Unit* UnitWidget::getUnitPtr(){
    return this->unitPtr_;
}

void UnitWidget::setCurrentTileWidget(TileWidget* tileWidgetPtr){
    this->setParentItem(tileWidgetPtr);
    this->tileWidgetPtr_ = tileWidgetPtr;
}
#include "unitWidget.hpp"

UnitWidget::UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr){
    this->unit_ = unitType;
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

void UnitWidget::setCurrentTileWidget(TileWidget* tileWidgetPtr){
    this->setParentItem(tileWidgetPtr);
    this->tileWidgetPtr_ = tileWidgetPtr;
}
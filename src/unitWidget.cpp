#include "unitWidget.hpp"
#include "unit.hpp"

UnitWidget::UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr, Unit* unitPtr){
    int scaleFactor = 40;
    this->setRect(20, 20, scaleFactor, scaleFactor);
    if(unitType == footman){
        this->setBrush(QBrush(Qt::red, Qt::Dense1Pattern));
    }
    else if(unitType == archer){
        this->setBrush(QBrush(Qt::yellow, Qt::Dense1Pattern));
    }

    this->unitPtr_ = unitPtr;

    this->healthLabelPtr_ = new QGraphicsSimpleTextItem(this);
    healthLabelPtr_->setText(QString::number(this->unitPtr_->getHealth()));
    healthLabelPtr_->setPos(5, 5);

    this->setCurrentTileWidget(destinationTileWidgetPtr);
}

void UnitWidget::updateHealthLabel(){
    this->healthLabelPtr_->setText(QString::number(this->unitPtr_->getHealth()));
    return;
}

TileWidget* UnitWidget::getTileWidgetPtr(){
    return this->tileWidgetPtr_;
}

Unit* UnitWidget::getUnitPtr(){
    return this->unitPtr_;
}

QGraphicsSimpleTextItem* UnitWidget::getHealthLabelPtr(){
    return this->healthLabelPtr_;
};

void UnitWidget::setCurrentTileWidget(TileWidget* tileWidgetPtr){
    this->setParentItem(tileWidgetPtr);
    this->tileWidgetPtr_ = tileWidgetPtr;
}
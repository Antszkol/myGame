#include "unitWidget.hpp"
#include "unit.hpp"
#include "player.hpp"

UnitWidget::UnitWidget(UnitType unitType, TileWidget* destinationTileWidgetPtr, Unit* unitPtr){
    int scaleFactor = 80;
    QPixmap pixmap;
    this->unitPtr_ = unitPtr;

    if(this->unitPtr_->getOwnerPtr()->getPlayerIdx() == 1){
        if(unitType == footman ){
            pixmap.load("../img/HumanFootmanNormal1.png");
        }
        else if(unitType == archer){
            pixmap.load("../img/HumanArcherNormal1.png");
        }
    }

    else if(this->unitPtr_->getOwnerPtr()->getPlayerIdx() == 2){
        if(unitType == footman ){
            pixmap.load("../img/HumanFootmanNormal2.png");
        }
        else if(unitType == archer){
            pixmap.load("../img/HumanArcherNormal2.png");
        }
    }
    
    this->setPixmap(pixmap.scaled(scaleFactor, scaleFactor));
    this->setOffset(0, 0); 

    this->healthLabelPtr_ = new QGraphicsSimpleTextItem(this);
    healthLabelPtr_->setText(QString::number(this->unitPtr_->getHealth()));
    healthLabelPtr_->setPos(5, 5);

    this->moraleLabelPtr_ = new QGraphicsSimpleTextItem(this);
    moraleLabelPtr_->setText(QString::number(50));
    moraleLabelPtr_->setPos(scaleFactor - moraleLabelPtr_->boundingRect().width() - 5, 5);

    this->setCurrentTileWidget(destinationTileWidgetPtr);
}

void UnitWidget::updateHealthLabel(){
    this->healthLabelPtr_->setText(QString::number(this->unitPtr_->getHealth()));
    return;
}

void UnitWidget::updateMoraleLabel(int morale){
    this->moraleLabelPtr_->setText(QString::number(morale));
    this->moraleLabelPtr_->setPos(80 - this->moraleLabelPtr_->boundingRect().width() - 5, 5);
    return;
}

void UnitWidget::setDeadPixmap() {
    QPixmap pixmap;
    UnitType unitType = this->unitPtr_->getUnitType();

    int scaleFactor = 80;

    if(this->unitPtr_->getOwnerPtr()->getPlayerIdx() == 1){
        if(unitType == footman ){
            pixmap.load("../img/HumanFootmanDead1.png");
        }
        else if(unitType == archer){
            pixmap.load("../img/HumanArcherDead1.png");
        }
    }

    else if(this->unitPtr_->getOwnerPtr()->getPlayerIdx() == 2){
        if(unitType == footman ){
            pixmap.load("../img/HumanFootmanDead2.png");
        }
        else if(unitType == archer){
            pixmap.load("../img/HumanArcherDead2.png");
        }
    }

    this->setPixmap(pixmap.scaled(scaleFactor, scaleFactor));
    this->setOffset(0, 0); 
}

void UnitWidget::setCurrentTileWidget(TileWidget* tileWidgetPtr){
    this->setParentItem(tileWidgetPtr);
    this->tileWidgetPtr_ = tileWidgetPtr;
}

TileWidget* UnitWidget::getTileWidgetPtr(){
    return this->tileWidgetPtr_;
}

Unit* UnitWidget::getUnitPtr() const {
    return this->unitPtr_;
}

QGraphicsSimpleTextItem* UnitWidget::getHealthLabelPtr(){
    return this->healthLabelPtr_;
};

QGraphicsSimpleTextItem* UnitWidget::getMoraleLabelPtr(){
    return this->moraleLabelPtr_;
};
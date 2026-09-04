#pragma once
#include <QGraphicsRectItem>
#include <QBrush>

#include "tileWidget.hpp"
#include "unitType.hpp"

class Unit;

class UnitWidget : public QGraphicsRectItem {
    public:
        UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr, Unit* unitPtr);

        void setCurrentTileWidget(TileWidget* tileWidgetPtr);
        void updateHealthLabel();
        Unit* getUnitPtr();
        QGraphicsSimpleTextItem* getHealthLabelPtr();
        void setUnitPtr(Unit* unitPtr);
        TileWidget* getTileWidgetPtr();
    
    private:
        TileWidget* tileWidgetPtr_;
        Unit* unitPtr_;
        QGraphicsSimpleTextItem* healthLabelPtr_;
    };
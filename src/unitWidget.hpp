#pragma once
#include <QGraphicsRectItem>
#include <QBrush>

#include "tileWidget.hpp"
#include "unitType.hpp"

class Unit;

class UnitWidget : public QGraphicsRectItem {
    public:
        UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr);

        void setCurrentTileWidget(TileWidget* tileWidgetPtr);
        Unit* getUnitPtr();
        void setUnitPtr(Unit* unitPtr);
        TileWidget* getTileWidgetPtr();
    
    private:
        TileWidget* tileWidgetPtr_;
        Unit* unitPtr_;
    };
#pragma once

#include <QBrush>
#include <QGraphicsPixmapItem>

#include "tileWidget.hpp"
#include "unitType.hpp"

class Unit;

class UnitWidget : public QGraphicsPixmapItem {
    public:
        UnitWidget(UnitType unitType, TileWidget* destinationTileWidgetPtr, Unit* unitPtr);

        void updateHealthLabel();

        void setDeadPixmap();
        void setCurrentTileWidget(TileWidget* tileWidgetPtr);
        void setUnitPtr(Unit* unitPtr);

        Unit* getUnitPtr() const;
        QGraphicsSimpleTextItem* getHealthLabelPtr();
        TileWidget* getTileWidgetPtr();

    private:
        TileWidget* tileWidgetPtr_;
        Unit* unitPtr_;
        QGraphicsSimpleTextItem* healthLabelPtr_;
    };
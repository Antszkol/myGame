#pragma once
#include <QGraphicsRectItem>
#include <QBrush>

#include "tileWidget.hpp"
#include "unit.hpp"
#include "unitType.hpp"

class UnitWidget : public QGraphicsRectItem {
    public:
        UnitWidget(int unitType, TileWidget* destinationTileWidgetPtr);

        int unit_;

        void setCurrentTileWidget(TileWidget* tileWidgetPtr);
    
    private:
        TileWidget* tileWidgetPtr_;
    };
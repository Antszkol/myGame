#pragma once

#include <QFont>
#include <QBrush>
#include <QGraphicsPixmapItem>

#include "tileWidget.hpp"
#include "unitType.hpp"

class Unit;

/// @brief Graphical representation of a Unit: its sprite plus health/morale labels, parented to
/// the TileWidget it currently stands on.
class UnitWidget : public QGraphicsPixmapItem {
    public:
        /// @param unitType determines which sprite is loaded.
        /// @param destinationTileWidgetPtr tile to place this widget on initially.
        /// @param unitPtr the logic-side Unit this widget represents.
        UnitWidget(UnitType unitType, TileWidget* destinationTileWidgetPtr, Unit* unitPtr);

        /// @brief Refreshes the health label text from unitPtr_'s current remaining health.
        void updateHealthLabel();

        /// @param morale new morale value to display.
        void updateMoraleLabel(int morale);

        /// @brief Swaps the sprite to the "dead" variant for this unit type/owner.
        void setDeadPixmap();

        /// @brief Reparents this widget onto a new tile (used for both movement and deployment).
        /// @param tileWidgetPtr the tile to move this widget onto.
        void setCurrentTileWidget(TileWidget* tileWidgetPtr);

        /// @param unitPtr new logic-side Unit for this widget to represent.
        void setUnitPtr(Unit* unitPtr);

        /// @return the logic-side Unit this widget represents.
        Unit* getUnitPtr() const;

        /// @return the health label item.
        QGraphicsSimpleTextItem* getHealthLabelPtr();

        /// @return the morale label item.
        QGraphicsSimpleTextItem* getMoraleLabelPtr();

        /// @return the tile this widget currently stands on.
        TileWidget* getTileWidgetPtr();

    private:
        TileWidget* tileWidgetPtr_;
        Unit* unitPtr_;
        QGraphicsSimpleTextItem* healthLabelPtr_;
        QGraphicsSimpleTextItem* moraleLabelPtr_;
    };
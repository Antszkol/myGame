#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "unitType.hpp"
#include "player.hpp"
#include "unitStats.hpp"

/// @brief Unit-recruitment UI: one buy button per UnitType, showing cost/stats.
class ShopWidget : public QWidget {
    Q_OBJECT
    public:
        ShopWidget();

        /// @brief Subtracts unitType's cost from currentPlayerPtr's gold.
        /// @param currentPlayerPtr player making the purchase.
        /// @param unitType type of unit being purchased.
        void buyUnit(Player* currentPlayerPtr, UnitType unitType);

        QGridLayout* layout_;

    signals:
        /// @brief Emitted when a buy button is clicked; TurnHandler::recruitUnitSlot listens for
        /// this to validate and process the purchase.
        /// @param unitType type of unit requested.
        void unitPurchaseRequested(UnitType unitType);
    };
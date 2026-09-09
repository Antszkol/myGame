#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <string>

#include "unitType.hpp"
#include "player.hpp"
#include "unitStats.hpp"
#include "actionMode.hpp"

/// @brief Turn-control UI: current player/gold display, move/attack/end-turn buttons, and the
/// live combat log line.
class ActionWidget : public QWidget {
    Q_OBJECT
    public:
        /// @param startingPlayerIdx player index to display initially.
        ActionWidget(int startingPlayerIdx = 1);

        /// @brief Updates the displayed current-player and gold labels.
        /// @param currentPlayerPtr player whose stats should be shown.
        void setCurrentPlayerStats(Player* currentPlayerPtr);

        /// @brief Updates the combat log label with the latest event text.
        /// @param messageText text to display (see Logger::getLastMessageText).
        void setLastMessage(const std::string& messageText);

        QVBoxLayout* layout_;

    private:
        QLabel* currentPlayerLabel_;
        QLabel* currentPlayerGoldLabel_;
        QLabel* combatLogLabel_;
        int currentPlayerIdx_;
        int currentPlayerGold_;

    signals:
        /// @brief Emitted when the Move button is clicked; TurnHandler::moveUnitSlot listens for this.
        void moveUnitRequested();
        /// @brief Emitted when the Attack button is clicked; TurnHandler::attackUnitSlot listens for this.
        void attackUnitRequested();
        /// @brief Emitted when the End turn button is clicked; TurnHandler::endTurnSlot listens for this.
        void endTurnRequested();
    };
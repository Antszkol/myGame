#pragma once
#include <QObject>
#include <utility>
#include "shopWidget.hpp"
#include "tileWidget.hpp"
#include "player.hpp"
#include "unitWidget.hpp"
#include "actionMode.hpp"
#include "actionWidget.hpp"
#include "unitStats.hpp"
#include "unitType.hpp"
#include "unitWidget.hpp"
#include "logger.hpp"
#include "battleSettings.hpp"

class BattleWidget;
class AIHandler;

/// @brief Owns both Players and drives the whole turn/battle flow: movement, attacks, unit
/// deployment, turn switching (including handing off to AIHandler), and the combat log.
class TurnHandler : public QObject {
    Q_OBJECT
    public slots:
        /// @brief Starts recruiting unitTypeIdx if the current player can afford it and is under
        /// the unit-count limit; actual placement happens on the next confirmUnitDeployment.
        void recruitUnitSlot(UnitType unitTypeIdx);
        /// @brief Enters attack-selection ActionMode for the current player.
        void attackUnitSlot();
        /// @brief Enters move-selection ActionMode for the current player.
        void moveUnitSlot();
        /// @brief Slot wrapper around endTurn().
        void endTurnSlot();

    signals:
        /// @brief Emitted when a unit reaches the opposing deployment zone, ending the battle.
        /// @param winnerPtr the winning player.
        void battleEnded(const Player* winnerPtr);

    public:
        /// @param battleWidgetPtr owning widget, used to reach the map/UI.
        /// @param shopWidgetPtr shop UI to wire purchase signals from.
        /// @param actionWidgetPtr action UI to wire turn/move/attack signals from and push status
        /// text to.
        /// @param lastMapColumn last column index of the map, used as Player 2's deployment column.
        /// @param isAI whether Player 2's turns are driven by AIHandler.
        /// @param battleSettingPtr battle settings (start gold, unit limit, game mode).
        TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr, int lastMapColumn, bool isAI, BattleSetting* battleSettingPtr);

        /// @brief Moves a unit and checks the win condition (destination in the enemy deployment
        /// zone), emitting battleEnded if met.
        /// @param tileWidgetStart tile the unit is moving from.
        /// @param tileWidgetDest tile the unit is moving to.
        void moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);

        /// @brief Resolves an attack: rolls luck damage, applies the morale multiplier, and either
        /// damages or kills the defender.
        /// @param tileWidgetStart attacking unit's tile.
        /// @param tileWidgetDest defending unit's tile.
        void attackUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);

        /// @brief Places the pending recruited unit onto a tile, if currently in RecruitUnit mode.
        /// @param tileWidgetPtr tile to deploy the unit onto.
        void confirmUnitDeployment(TileWidget* tileWidgetPtr);

        /// @brief Switches the current player, refreshes their units' speed, and hands off to
        /// AIHandler if the new current player is AI-controlled.
        void endTurn();

        /// @param aiHandlerPtr AI handler to drive Player 2's turns, once GameMode is VsAI.
        void setAIHandler(AIHandler* aiHandlerPtr);

        /// @param actionMode new ActionMode for the current player.
        void setActionMode(ActionMode actionMode);

        /// @brief Recomputes and updates the displayed morale for every living unit on the map.
        void refreshUnitMorale();

        /// @return the current player's ActionMode.
        ActionMode getActionMode(){return this->actionMode_;};

        /// @param playerIdx 1 or 2.
        /// @return the corresponding Player.
        Player* getPlayerPtr(int playerIdx);

        /// @return the action UI widget.
        ActionWidget* getActionWidgetPtr();

        /// @return the player whose turn it currently is.
        Player* getCurrentPlayerPtr();

        /// @return the player whose turn it is NOT.
        Player* getNotCurrentPlayerPtr();

        /// @return the combat log for this battle.
        Logger* getLoggerPtr();

    private:
        int turnNumber_;
        bool isTurnFinished_;
        std::pair<Player*, Player*> players_;
        std::map<Unit*, int> currentSpeedMap_;
        AIHandler* aiHandlerPtr_;
        Player* currentPlayerPtr_;
        BattleWidget* battleWidgetPtr_;
        BattleSetting* battleSettingPtr_;
        ShopWidget* shopWidgetPtr_;
        ActionWidget* actionWidgetPtr_;
        ActionMode actionMode_;
        UnitType pendingUnitType_;
        Logger logger_;
};
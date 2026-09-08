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

class TurnHandler : public QObject {
    Q_OBJECT
    public slots:
        void recruitUnitSlot(UnitType unitTypeIdx);
        void attackUnitSlot();
        void moveUnitSlot();
        void endTurnSlot();

    signals:
        void battleEnded(const Player* winnerPtr);

    public:
        TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr, int lastMapColumn, bool isAI, BattleSetting* battleSettingPtr);
            
        void moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);
        void attackUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);
        void confirmUnitDeployment(TileWidget* tileWidgetPtr);
        void endTurn();

        void setAIHandler(AIHandler* aiHandlerPtr);
        void setActionMode(ActionMode actionMode);
        void refreshUnitMorale();

        ActionMode getActionMode(){return this->actionMode_;};
        Player* getPlayerPtr(int playerIdx);
        ActionWidget* getActionWidgetPtr();
        Player* getCurrentPlayerPtr();
        Player* getNotCurrentPlayerPtr();
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
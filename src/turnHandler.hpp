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

class BattleWidget; // no include because of circular include

class TurnHandler : public QObject {
    public slots:
        void recruitUnitSlot(UnitType unitTypeIdx);
        void attackUnitSlot();
        void moveUnitSlot();
        void switchPlayerSlot();

    public:
        TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr, ActionWidget* actionWidgetPtr, int lastMapColumn);
            
        ActionMode getActionMode(){return this->actionMode_;};    
        void moveUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);
        void attackUnit(TileWidget* tileWidgetStart, TileWidget* tileWidgetDest);
        void confirmUnitDeployment(TileWidget* tileWidgetPtr);
        void switchPlayer();
        void setActionMode(ActionMode actionMode);

        Player* getPlayerPtr(int playerIdx);
        ActionWidget* getActionWidgetPtr();
        Player* getCurrentPlayerPtr();

    private:
        int turnNumber_;
        bool isTurnFinished_;
        std::pair<Player*, Player*> players_;
        std::map<Unit*, int> currentSpeedMap_;
        Player* currentPlayerPtr_;
        BattleWidget* battleWidgetPtr_;
        ShopWidget* shopWidgetPtr_;
        ActionWidget* actionWidgetPtr_;
        ActionMode actionMode_;
        UnitType pendingUnitType_;
};
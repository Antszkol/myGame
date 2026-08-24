#pragma once
#include <QObject>
#include "shopWidget.hpp"
#include "tileWidget.hpp"
#include "player.hpp"
#include "unitWidget.hpp"
#include "actionMode.hpp"

class BattleWidget; // no include because of circular include

class TurnHandler : public QObject {
    public slots:
        void recruitUnit(Player* currentPlayerPtr, UnitType unitTypeIdx);

    public:
        TurnHandler(BattleWidget* battleWidgetPtr, ShopWidget* shopWidgetPtr);
            
        ActionMode getActionMode(){return this->actionMode_;};    
        void confirmUnitDeployment(TileWidget* tileWidgetPtr);

    private:
        int turnNumber_;
        bool isTurnFinished_;
        pair<Player*, Player*> players_;
        Player* currentPlayer_;
        BattleWidget* battleWidgetPtr_;
        ShopWidget* shopWidgetPtr_;
        ActionMode actionMode_;
        UnitType pendingUnitType_;
};
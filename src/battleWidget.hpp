#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "shopWidget.hpp"
#include "baseScreenWidget.hpp"
#include "battleSettings.hpp"
#include "mapWidget.hpp"
#include "battle.hpp"
#include "shopWidget.hpp"
#include "turnHandler.hpp"
#include "actionWidget.hpp"

class BattleWidget : public BaseScreenWidget{
    Q_OBJECT
    public slots:
        void setBattle(Battle* battlePtr, BattleSetting* battleSettingPtr);

    public:
        BattleWidget();
        ~BattleWidget();

        void setShop();
        MapWidget* getMapWidgetPtr();

    private:
        QHBoxLayout* layout_;
        MapWidget* mapWidgetPtr_;
        BattleSetting* battleSettingPtr_;
        ShopWidget* shopWidgetPtr_;
        TurnHandler* turnHandlerPtr_;
        Battle* battlePtr_;
        QLabel* goldLabel_;
};
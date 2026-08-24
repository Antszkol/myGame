#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "battleSettings.hpp"
#include "battleWidget.hpp"
#include "battleSettingsWidget.hpp"

class BattleMenuWidget : public BaseScreenWidget{
    Q_OBJECT
    signals:
        void battleCreated(Battle* battlePtr, BattleSetting* battleSettingPtr);
    
    public slots:
        void createBattle();

    public:
        BattleMenuWidget(BattleSetting* battleSettingPtr);
        ~BattleMenuWidget();

    private:
        BattleSettingsWidget* battleSettingsWidgetPtr_;
};
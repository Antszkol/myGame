#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "battleSettings.hpp"
#include "battleWidget.hpp"
#include "battleSettingsWidget.hpp"

/// @brief Pre-battle screen: hosts battle settings (start gold, unit limit, game mode) and
/// creates the Battle/Map on confirm.
class BattleMenuWidget : public BaseScreenWidget{
    Q_OBJECT
    signals:
        /// @brief Emitted once a new battle is ready to be shown.
        /// @param battlePtr the created battle.
        /// @param battleSettingPtr the settings it was created with.
        void battleCreated(Battle* battlePtr, BattleSetting* battleSettingPtr);

    public slots:
        /// @brief Builds a new Map/Battle from the current settings and emits battleCreated.
        void createBattle();

    public:
        /// @param battleSettingPtr settings to configure this battle with; also passed to the
        /// BattleSettingsWidget for editing.
        BattleMenuWidget(BattleSetting* battleSettingPtr);
        ~BattleMenuWidget();

    private:
        BattleSettingsWidget* battleSettingsWidgetPtr_;
};
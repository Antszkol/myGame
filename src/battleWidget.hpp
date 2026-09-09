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

/// @brief The actual battle screen: hosts the map, shop, and action UI, and owns the TurnHandler (and
/// AIHandler, for VsAI battles) driving the current battle.
class BattleWidget : public BaseScreenWidget{
    Q_OBJECT
    public slots:
        /// @brief Starts a new battle: (re)creates TurnHandler/MapWidget (and AIHandler if
        /// GameMode::VsAI) for battlePtr/battleSettingPtr.
        /// @param battlePtr the battle to show.
        /// @param battleSettingPtr the settings it was created with.
        void setBattle(Battle* battlePtr, BattleSetting* battleSettingPtr);

        /// @brief Shows the result screen, deletes the map, and navigates back to the menu.
        /// @param winnerPtr the winning player.
        void battleEnded(const Player* winnerPtr);

    public:
        BattleWidget();
        ~BattleWidget();

        /// @brief Creates and docks the shop widget into the layout.
        void setShopWidget();

        /// @brief Creates and docks the action widget into the layout.
        void setActionWidget();

        /// @return the current battle's map widget, or nullptr if none is active.
        MapWidget* getMapWidgetPtr();

    private:
        QHBoxLayout* layout_;
        MapWidget* mapWidgetPtr_ = nullptr;
        BattleSetting* battleSettingPtr_;
        ShopWidget* shopWidgetPtr_;
        ActionWidget* actionWidgetPtr_;
        std::unique_ptr<TurnHandler> turnHandlerPtr_;
        Battle* battlePtr_;
        QLabel* goldLabel_;
};
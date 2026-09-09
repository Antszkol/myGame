#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "settings.hpp"

/// @brief Main menu screen: entry points to starting a battle and opening settings.
class MenuWidget : public BaseScreenWidget{
    Q_OBJECT
    public:
        /// @param settingsPtr app settings, passed through to the settings dialog.
        MenuWidget(Setting* settingsPtr);
        ~MenuWidget();

    private:
        Setting* settingsPtr_;
};
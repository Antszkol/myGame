#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "settings.hpp"

class MenuWidget : public BaseScreenWidget{
    Q_OBJECT
    public:
        MenuWidget(Setting* settingsPtr);
        ~MenuWidget();

    private:
        Setting* settingsPtr_;
};
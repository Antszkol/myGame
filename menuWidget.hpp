#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "settings.hpp"

class menuWidget : public baseScreenWidget{
    Q_OBJECT
    public:
        menuWidget(setting* settingsPtr);
        ~menuWidget();
    
    private:
        setting* settingsPtr;
};
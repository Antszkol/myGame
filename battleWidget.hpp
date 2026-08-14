#pragma once
#include <QWidget>
#include "baseScreenWidget.hpp"
#include "battleSettings.hpp"

class battleWidget : public baseScreenWidget{
    Q_OBJECT
    public:
        battleWidget(battleSetting* battleSettingPtr);
        ~battleWidget();

    private:
        battleSetting* battleSettingPtr;
};
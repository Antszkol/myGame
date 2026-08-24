#pragma once
#include <QWidget>
#include "screen.hpp"

class MenuWidget;
class BattleMenuWidget;

class BaseScreenWidget : public QWidget{
    Q_OBJECT

    signals:
        void screenChanged(Screen target);

    public:
        BaseScreenWidget();

    public slots:
        void navigateTo(Screen target);
};
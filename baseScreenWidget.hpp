#pragma once
#include <QWidget>
#include "screen.hpp"

class menuWidget;
class battleWidget;

class baseScreenWidget : public QWidget{
    Q_OBJECT

    signals:
        void screenChanged(Screen target);

    public:
        baseScreenWidget();

    public slots:
        void navigateTo(Screen target);
};
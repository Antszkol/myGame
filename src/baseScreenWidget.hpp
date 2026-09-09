#pragma once
#include <QWidget>
#include "screen.hpp"

class MenuWidget;
class BattleMenuWidget;

/// @brief Common base for every top-level screen widget; provides navigation between screens via
/// a signal MainWidget listens to.
class BaseScreenWidget : public QWidget{
    Q_OBJECT

    signals:
        /// @brief Emitted by navigateTo to request MainWidget switch the visible screen.
        /// @param target screen to switch to.
        void screenChanged(Screen target);

    public:
        BaseScreenWidget();

    public slots:
        /// @brief Requests a screen switch by emitting screenChanged.
        /// @param target screen to switch to.
        void navigateTo(Screen target);
};
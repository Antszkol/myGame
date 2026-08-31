#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "unitType.hpp"
#include "player.hpp"
#include "unitStats.hpp"
#include "actionMode.hpp"

class ActionWidget : public QWidget {
    Q_OBJECT
    public:
        ActionWidget(int startingPlayerIdx = 1);

        void setCurrentPlayerStats(Player* currentPlayerPtr);

        QVBoxLayout* layout_;

    private:
        QLabel* currentPlayerLabel_;
        QLabel* currentPlayerGoldLabel_;
        int currentPlayerIdx_;
        int currentPlayerGold_;

    signals:
        void moveUnitRequested();
        void attackUnitRequested(UnitType unitType);
        void endTurnRequested();
        void findPathsRequested();
    };
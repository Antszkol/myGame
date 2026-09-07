#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <string>

#include "unitType.hpp"
#include "player.hpp"
#include "unitStats.hpp"
#include "actionMode.hpp"

class ActionWidget : public QWidget {
    Q_OBJECT
    public:
        ActionWidget(int startingPlayerIdx = 1);

        void setCurrentPlayerStats(Player* currentPlayerPtr);
        void setLastMessage(const std::string& messageText);

        QVBoxLayout* layout_;

    private:
        QLabel* currentPlayerLabel_;
        QLabel* currentPlayerGoldLabel_;
        QLabel* combatLogLabel_;
        int currentPlayerIdx_;
        int currentPlayerGold_;

    signals:
        void moveUnitRequested();
        void attackUnitRequested();
        void endTurnRequested();
        void findPathsRequested();
    };
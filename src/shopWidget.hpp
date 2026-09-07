#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "unitType.hpp"
#include "player.hpp"
#include "unitStats.hpp"

class ShopWidget : public QWidget {
    Q_OBJECT
    public:
        ShopWidget();

        void buyUnit(Player* currentPlayerPtr, UnitType unitType);

        QGridLayout* layout_;

    signals:
        void unitPurchaseRequested(UnitType unitType);
    };
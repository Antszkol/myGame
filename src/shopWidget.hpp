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

        QGridLayout* layout_;
        void buyUnit(Player* currentPlayerPtr, UnitType unitType);

    signals:
        void unitPurchaseRequested(UnitType unitType);
    };
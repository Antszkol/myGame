#include <QGridLayout>
#include <QPushButton>
#include <QString>

#include "shopWidget.hpp"

ShopWidget::ShopWidget(){
    this->layout_ = new QGridLayout(this);

    int i = 0;
    for (const auto& [type, name] : UnitTypeMap){
        QPushButton* itemButton = new QPushButton(QString::fromStdString(name), this);
        layout_->addWidget(itemButton, i / 4, i % 2);
        connect(itemButton, &QPushButton::clicked, this, [this, type](){
            emit unitPurchaseRequested(type);
        });
        i++;
    }
}

void ShopWidget::buyUnit(Player* currentPlayerPtr, UnitType unitType){
    currentPlayerPtr->subtractGold(UnitStatsMap.at(unitType).cost_);
    return;
}
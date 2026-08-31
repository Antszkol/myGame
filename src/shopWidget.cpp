#include <QGridLayout>
#include <QPushButton>
#include <QString>

#include "shopWidget.hpp"

ShopWidget::ShopWidget(){
    this->layout_ = new QGridLayout(this);
    QLabel* label = new QLabel("Recruit Units", this);
    this->layout_->addWidget(label, 0, 0, 1, 2, Qt::AlignCenter);
    int i = 0;
    for (const auto& [type, name] : UnitTypeMap){
        QPushButton* itemButton = new QPushButton(QString::fromStdString(name), this);
        layout_->addWidget(itemButton, 1 + i / 2, i % 2, Qt::AlignCenter);
        connect(itemButton, &QPushButton::clicked, this, [this, type](){
            emit unitPurchaseRequested(type);
        });
        i++;
    }
    int rowCount = 1 + (i - 1) / 2 + 1;
    for(int row = 0; row < rowCount; ++row){
        this->layout_->setRowStretch(row, 1);
    }
}

void ShopWidget::buyUnit(Player* currentPlayerPtr, UnitType unitType){
    currentPlayerPtr->subtractGold(UnitStatsMap.at(unitType).cost_);
    return;
}
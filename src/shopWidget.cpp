#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>

#include "shopWidget.hpp"

ShopWidget::ShopWidget(){
    this->layout_ = new QGridLayout(this);
    this->layout_->setContentsMargins(16, 32, 16, 32);
    QLabel* label = new QLabel("Recruit Units", this);
    label->setStyleSheet("font-size: 24pt;");
    this->layout_->addWidget(label, 0, 0, Qt::AlignCenter);
    this->layout_->setRowMinimumHeight(1, 24);

    QHBoxLayout* buttonRowLayout = new QHBoxLayout();
    buttonRowLayout->addStretch();
    for (const auto& [type, name] : UnitTypeMap){
        QPushButton* itemButton = new QPushButton(QString::fromStdString(name), this);
        buttonRowLayout->addWidget(itemButton);
        connect(itemButton, &QPushButton::clicked, this, [this, type](){
            emit unitPurchaseRequested(type);
        });
    }
    buttonRowLayout->addStretch();
    this->layout_->addLayout(buttonRowLayout, 2, 0);

    this->layout_->setRowStretch(3, 1);
}

void ShopWidget::buyUnit(Player* currentPlayerPtr, UnitType unitType){
    currentPlayerPtr->subtractGold(UnitStatsMap.at(unitType).cost_);
    return;
}
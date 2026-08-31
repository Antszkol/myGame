#include <QGridLayout>
#include <QPushButton>
#include <QString>

#include "actionWidget.hpp"

ActionWidget::ActionWidget(int startingPlayerIdx){
    this->layout_ = new QVBoxLayout(this);

    this->currentPlayerLabel_ = new QLabel(this);
    this->layout_->addWidget(currentPlayerLabel_);
    
    this->currentPlayerGoldLabel_ = new QLabel(this);
    this->layout_->addWidget(currentPlayerGoldLabel_);

    QLabel* actionLabel = new QLabel("ACTIONS", this);
    this->layout_->addWidget(actionLabel);

    int i = 0;
    for (const auto& [mode, name] : ActionModeMap){
        if(mode != ActionMode::RecruitUnit && mode != ActionMode::None){
            QPushButton* itemButton = new QPushButton(QString::fromStdString(name), this);
            if(mode == ActionMode::MoveUnit){
                connect(itemButton, &QPushButton::clicked, this, [this](){
                    emit moveUnitRequested();
                });
            }
            layout_->addWidget(itemButton);
            i++;
        }
    }
    QPushButton* endTurnButton = new QPushButton(QString::fromStdString("End turn"), this);
    this->layout_->addWidget(endTurnButton);
    connect(endTurnButton, &QPushButton::clicked, this, [this](){
            emit endTurnRequested();
        });
    /*
    int rowCount = 1 + (i - 1) / 2 + 1;
    for(int row = 0; row < rowCount; ++row){
        this->layout_->setRowStretch(row, 1);
    }
    */
}

void ActionWidget::setCurrentPlayerStats(Player* currentPlayerPtr){
    this->currentPlayerIdx_ = currentPlayerPtr->getPlayerIdx();
    this->currentPlayerLabel_->setText(QString("Current player: %1").arg(this->currentPlayerIdx_));
    this->currentPlayerGold_ = currentPlayerPtr->getGold();
    this->currentPlayerGoldLabel_->setText(QString("Gold: %1").arg(this->currentPlayerGold_));
    return;
}
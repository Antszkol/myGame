#include <QGridLayout>
#include <QPushButton>
#include <QString>

#include "actionWidget.hpp"

ActionWidget::ActionWidget(int startingPlayerIdx){
    this->setStyleSheet(
        "QWidget {"
        "   font-family: \"EB Garamond\";"
        "   font-style: italic;"
        "}"
    );

    this->layout_ = new QVBoxLayout(this);
    this->layout_->setContentsMargins(32, 32, 32, 32);

    this->currentPlayerLabel_ = new QLabel(this);
    currentPlayerLabel_->setAlignment(Qt::AlignCenter);
    currentPlayerLabel_->setStyleSheet("font-size: 24pt;");
   
    this->layout_->addWidget(currentPlayerLabel_);

    this->layout_->addSpacing(32);

    this->currentPlayerGoldLabel_ = new QLabel(this);
    currentPlayerGoldLabel_->setAlignment(Qt::AlignCenter);
    currentPlayerGoldLabel_->setStyleSheet("font-size: 24pt;");
    this->layout_->addWidget(currentPlayerGoldLabel_);

    this->layout_->addSpacing(32);

    this->combatLogLabel_ = new QLabel(this);
    this->combatLogLabel_->setWordWrap(true);
    combatLogLabel_->setAlignment(Qt::AlignCenter);
    combatLogLabel_->setStyleSheet("font-size: 20pt;");
    this->layout_->addWidget(combatLogLabel_);

    this->layout_->addSpacing(32);

    QLabel* actionLabel = new QLabel("Actions", this);
    actionLabel->setAlignment(Qt::AlignCenter);
    actionLabel->setStyleSheet("font-size: 24pt;");
    this->layout_->addWidget(actionLabel);
    this->layout_->addSpacing(12);

    int i = 0;
    for (const auto& [mode, name] : ActionModeMap){
        if(mode != ActionMode::RecruitUnit && mode != ActionMode::None){
            QPushButton* itemButton = new QPushButton(QString::fromStdString(name), this);
            itemButton->setStyleSheet("font-size: 20pt;");
            if(mode == ActionMode::MoveUnit){
                connect(itemButton, &QPushButton::clicked, this, [this](){
                    emit moveUnitRequested();
                });
            }
            if(mode == ActionMode::AttackUnit){
                connect(itemButton, &QPushButton::clicked, this, [this](){
                    emit attackUnitRequested();
                });
            }
            layout_->addWidget(itemButton);
            this->layout_->addSpacing(12);
            i++;
        }
    }

    QPushButton* endTurnButton = new QPushButton(QString::fromStdString("End turn"), this);
    endTurnButton->setStyleSheet("font-size: 20pt;");
    this->layout_->addWidget(endTurnButton);
    connect(endTurnButton, &QPushButton::clicked, this, [this](){
            emit endTurnRequested();
        });

    this->layout_->addStretch();
}

void ActionWidget::setCurrentPlayerStats(Player* currentPlayerPtr){
    this->currentPlayerIdx_ = currentPlayerPtr->getPlayerIdx();
    this->currentPlayerLabel_->setText(QString("Current player: %1").arg(this->currentPlayerIdx_));
    this->currentPlayerGold_ = currentPlayerPtr->getGold();
    this->currentPlayerGoldLabel_->setText(QString("Gold: %1").arg(this->currentPlayerGold_));
    return;
}

void ActionWidget::setLastMessage(const std::string& messageText){
    this->combatLogLabel_->setText(QString::fromStdString(messageText));
    return;
}
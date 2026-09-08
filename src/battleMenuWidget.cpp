#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "battle.hpp"
#include "baseScreenWidget.hpp"
#include "battleMenuWidget.hpp"
#include "battleSettingsWidget.hpp"

BattleMenuWidget::BattleMenuWidget(BattleSetting* battleSettingPtr){
    this->battleSettingsWidgetPtr_ = new BattleSettingsWidget(battleSettingPtr, this);
    this->setAttribute(Qt::WA_StyledBackground, true);

    QPushButton* battleButton = new QPushButton("Start Battle!", this);
    battleButton->setStyleSheet("font-size: 24pt;");
    QPushButton* battleSettingsButton = new QPushButton("Battle Settings", this);
    battleSettingsButton->setStyleSheet("font-size: 24pt;");
    QPushButton* backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("font-size: 24pt;");

    connect(battleButton, &QPushButton::clicked, this, [this](){
        navigateTo(Screen::battleWidget);
        createBattle();
    });
    connect(backButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::menuWidget);});
    connect(battleSettingsButton, &QPushButton::clicked, this, [this](){
        BattleSettingsWidget* dialog = new BattleSettingsWidget(this->battleSettingsWidgetPtr_->getBattleSetting(), this);
        dialog->exec();
    });

    QVBoxLayout* layout = new QVBoxLayout(this);
    for(QPushButton* button : {battleButton, battleSettingsButton, backButton}){
        QHBoxLayout* buttonRowLayout = new QHBoxLayout();
        buttonRowLayout->addStretch(1);
        buttonRowLayout->addWidget(button, 1);
        buttonRowLayout->addStretch(1);
        layout->addLayout(buttonRowLayout);
    }
}

BattleMenuWidget::~BattleMenuWidget(){}

void BattleMenuWidget::createBattle(){
    Map* mapPtr = new Map({10, 10});
    Battle* battlePtr = new Battle(mapPtr, battleSettingsWidgetPtr_->getBattleSetting());
    emit battleCreated(battlePtr, battleSettingsWidgetPtr_->getBattleSetting());
}
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "battle.hpp"
#include "baseScreenWidget.hpp"
#include "battleMenuWidget.hpp"
#include "battleSettingsWidget.hpp"

BattleMenuWidget::BattleMenuWidget(BattleSetting* battleSettingPtr){
    this->battleSettingsWidgetPtr_ = new BattleSettingsWidget(battleSettingPtr, this);
    
    QFont font("Garamond", 16);
    this->setFont(font);

    QPushButton* battleButton = new QPushButton("Start Battle!", this);
    QPushButton* battleSettingsButton = new QPushButton("Battle Settings", this);
    QPushButton* backButton = new QPushButton("Back", this);

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
    layout->addWidget(battleButton);
    layout->addWidget(battleSettingsButton);
    layout->addWidget(backButton);
}

BattleMenuWidget::~BattleMenuWidget(){}

void BattleMenuWidget::createBattle(){
    Map* mapPtr = new Map({10, 10});
    Battle* battlePtr = new Battle(mapPtr, battleSettingsWidgetPtr_->getBattleSetting());
    emit battleCreated(battlePtr, battleSettingsWidgetPtr_->getBattleSetting());
}
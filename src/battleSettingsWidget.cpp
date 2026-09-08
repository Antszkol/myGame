#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFont>
#include <QApplication>
#include <QString>
#include <QVariant>
#include "battleSettingsWidget.hpp"

BattleSettingsWidget::BattleSettingsWidget(BattleSetting* battleSettingPtr, QWidget* parent) : QDialog(parent){
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->battleSettingPtr_ = battleSettingPtr;

    startGoldSpinBox_ = new QSpinBox(this);
    startGoldSpinBox_->setRange(0, 1000);
    startGoldSpinBox_->setValue(battleSettingPtr->getStartGold());

    maxUnitSpinBox_ = new QSpinBox(this);
    maxUnitSpinBox_->setRange(0, 20);
    maxUnitSpinBox_->setValue(battleSettingPtr->getMaxUnit());

    gameModeComboBox_ = new QComboBox(this);
    for(const auto& [mode, name] : GameModeMap){
        gameModeComboBox_->addItem(QString::fromStdString(name), QVariant::fromValue(static_cast<int>(mode)));
    }
    int currentModeIndex = gameModeComboBox_->findData(QVariant::fromValue(static_cast<int>(battleSettingPtr->getGameMode())));
    if(currentModeIndex != -1){
        gameModeComboBox_->setCurrentIndex(currentModeIndex);
    }

    saveButton_ = new QPushButton("Save Battle Settings", this);
    connect(saveButton_, &QPushButton::clicked, this, &BattleSettingsWidget::onSaveClicked);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Start gold amount:", startGoldSpinBox_);
    layout->addRow("Max unit count:", maxUnitSpinBox_);
    layout->addRow("Game mode:", gameModeComboBox_);
    layout->addRow(saveButton_);
}

BattleSettingsWidget::~BattleSettingsWidget(){}

void BattleSettingsWidget::onSaveClicked(){
    GameMode selectedGameMode = static_cast<GameMode>(gameModeComboBox_->currentData().toInt());
    this->battleSettingPtr_->saveBattleSettings(startGoldSpinBox_->value(), maxUnitSpinBox_->value(), selectedGameMode);

    accept();
}

BattleSetting* BattleSettingsWidget::getBattleSetting(){
    return this->battleSettingPtr_;
}
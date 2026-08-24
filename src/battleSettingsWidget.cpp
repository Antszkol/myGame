#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFont>
#include <QApplication>
#include "battleSettingsWidget.hpp"

BattleSettingsWidget::BattleSettingsWidget(BattleSetting* battleSettingPtr, QWidget* parent) : QDialog(parent){

    QFont font("Garamond", 16);
    this->setFont(font);

    this->battleSettingPtr_ = battleSettingPtr;

    startGoldSpinBox_ = new QSpinBox(this);
    startGoldSpinBox_->setRange(0, 1000);
    startGoldSpinBox_->setValue(battleSettingPtr->getStartGold());

    maxUnitSpinBox_ = new QSpinBox(this);
    maxUnitSpinBox_->setRange(0, 20);
    maxUnitSpinBox_->setValue(battleSettingPtr->getMaxUnit());

    saveButton_ = new QPushButton("Save Battle Settings", this);
    connect(saveButton_, &QPushButton::clicked, this, &BattleSettingsWidget::onSaveClicked);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Start gold amount:", startGoldSpinBox_);
    layout->addRow("Max unit count:", maxUnitSpinBox_);
    layout->addRow(saveButton_);
}

BattleSettingsWidget::~BattleSettingsWidget(){}

void BattleSettingsWidget::onSaveClicked(){
    this->battleSettingPtr_->saveBattleSettings(startGoldSpinBox_->value(), maxUnitSpinBox_->value());

    accept();
}

BattleSetting* BattleSettingsWidget::getBattleSetting(){
    return this->battleSettingPtr_;
}
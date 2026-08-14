#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFont>
#include <QApplication>
#include "battleSettingsWidget.hpp"

battleSettingsWidget::battleSettingsWidget(battleSetting* battleSettingPtr, QWidget* parent) : QDialog(parent){

    QFont font("Garamond", 16);
    this->setFont(font);

    this->battleSettingPtr = battleSettingPtr;

    startGoldSpinBox = new QSpinBox(this);
    startGoldSpinBox->setRange(0, 1000);
    startGoldSpinBox->setValue(battleSettingPtr->getStartGold());

    maxUnitSpinBox = new QSpinBox(this);
    maxUnitSpinBox->setRange(0, 20);
    maxUnitSpinBox->setValue(battleSettingPtr->getMaxUnit());

    saveButton = new QPushButton("Save Battle Settings", this);
    connect(saveButton, &QPushButton::clicked, this, &battleSettingsWidget::onSaveClicked);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Start gold amount:", startGoldSpinBox);
    layout->addRow("Max unit count:", maxUnitSpinBox);
    layout->addRow(saveButton);
}

battleSettingsWidget::~battleSettingsWidget(){}

void battleSettingsWidget::onSaveClicked(){
    this->battleSettingPtr->saveBattleSettings(startGoldSpinBox->value(), maxUnitSpinBox->value());

    accept();
}
#pragma once
#include <QWidget>
#include <QSpinBox>
#include <QDialog>
#include <QPushButton>
#include "battleSettings.hpp"

class battleSettingsWidget : public QDialog{
    Q_OBJECT
    public:
        battleSettingsWidget(battleSetting* battleSettingPtr, QWidget* parent);
        ~battleSettingsWidget();

        QSpinBox* startGoldSpinBox;
        QSpinBox* maxUnitSpinBox;
        QPushButton* saveButton;

    private slots:
        void onSaveClicked();

    private:
        battleSetting* battleSettingPtr;
};
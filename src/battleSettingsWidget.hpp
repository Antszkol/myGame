#pragma once
#include <QWidget>
#include <QSpinBox>
#include <QDialog>
#include <QPushButton>
#include "battleSettings.hpp"

class BattleSettingsWidget : public QDialog{
    Q_OBJECT
    public:
        BattleSettingsWidget(BattleSetting* battleSettingPtr, QWidget* parent);
        ~BattleSettingsWidget();

        QSpinBox* startGoldSpinBox_;
        QSpinBox* maxUnitSpinBox_;
        QPushButton* saveButton_;

        BattleSetting* getBattleSetting();

    private slots:
        void onSaveClicked();

    private:
        BattleSetting* battleSettingPtr_;
};
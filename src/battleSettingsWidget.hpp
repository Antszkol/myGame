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

        BattleSetting* getBattleSetting();

        QSpinBox* startGoldSpinBox_;
        QSpinBox* maxUnitSpinBox_;
        QPushButton* saveButton_;

    private slots:
        void onSaveClicked();

    private:
        BattleSetting* battleSettingPtr_;
};
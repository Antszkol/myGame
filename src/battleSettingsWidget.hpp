#pragma once
#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include "battleSettings.hpp"
#include "gameMode.hpp"

/// @brief QDialog for editing a BattleSetting: start gold, unit limit, and game mode.
class BattleSettingsWidget : public QDialog{
    Q_OBJECT
    public:
        /// @param battleSettingPtr settings to edit and save into.
        /// @param parent owning widget.
        BattleSettingsWidget(BattleSetting* battleSettingPtr, QWidget* parent);
        ~BattleSettingsWidget();

        /// @return the BattleSetting this dialog edits.
        BattleSetting* getBattleSetting();

        QSpinBox* startGoldSpinBox_;
        QSpinBox* maxUnitSpinBox_;
        QComboBox* gameModeComboBox_;
        QComboBox* mapTypeComboBox_;
        QPushButton* saveButton_;

    private slots:
        /// @brief Writes the current values back into battleSettingPtr_.
        void onSaveClicked();

    private:
        BattleSetting* battleSettingPtr_;
};
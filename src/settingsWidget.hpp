#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <utility>
#include "settings.hpp"

using namespace std;

/// @brief Dialog for editing app-wide Setting: window resolution.
class SettingsWidget : public QDialog {
    Q_OBJECT
    public:
        /// @param settingsPtr settings to edit and save into.
        /// @param parent optional owning widget.
        SettingsWidget(Setting* settingsPtr, QWidget* parent = nullptr);
        ~SettingsWidget();

        QComboBox* windowSizeComboBox_;
        QPushButton* saveButton_;

    private slots:
        /// @brief Writes the current values back into settingsPtr_.
        void onSaveClicked();

    private:
        Setting* settingsPtr_;
        vector<pair<int,int>> resolutions_;
};

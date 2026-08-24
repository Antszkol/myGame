#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <utility>
#include "settings.hpp"

using namespace std;

class SettingsWidget : public QDialog {
    Q_OBJECT
    public:
        SettingsWidget(Setting* settingsPtr, QWidget* parent = nullptr);
        ~SettingsWidget();

        QSpinBox* brightnessSpinBox_;
        QComboBox* windowSizeComboBox_;
        QPushButton* saveButton_;

    private slots:
        void onSaveClicked();

    private:
        Setting* settingsPtr_;
        vector<pair<int,int>> resolutions_;
};

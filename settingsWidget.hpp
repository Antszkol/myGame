#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <utility>
#include "settings.hpp"

using namespace std;

class settingsWidget : public QDialog {
    Q_OBJECT
    public:
        settingsWidget(setting* settingsPtr, QWidget* parent = nullptr);
        ~settingsWidget();

        QSpinBox* brightnessSpinBox;
        QComboBox* windowSizeComboBox;
        QPushButton* saveButton;

    private slots:
        void onSaveClicked();

    private:
        setting* settingsPtr;
        vector<pair<int,int>> resolutions;
};

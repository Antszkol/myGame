#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include "screen.hpp"
#include "menuWidget.hpp"
#include "battleWidget.hpp"
#include "battleSettingsWidget.hpp"
#include "baseScreenWidget.hpp"
#include "settings.hpp"
#include "battleSettings.hpp"

class mainWidget : public QWidget{
    Q_OBJECT
    public slots:
        void switchScreen(Screen target);

    public:
        mainWidget(QWidget *parent = nullptr);
        ~mainWidget();

        QStackedWidget* stack;
        setting* settingsPtr;
        battleSetting* battleSettingPtr;
};
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include "screen.hpp"
#include "battle.hpp"
#include "menuWidget.hpp"
#include "battleWidget.hpp"
#include "battleMenuWidget.hpp"
#include "battleSettingsWidget.hpp"
#include "baseScreenWidget.hpp"
#include "settings.hpp"
#include "battleSettings.hpp"

class MainWidget : public QWidget{
    Q_OBJECT
    public slots:
        void switchScreen(Screen target);

    public:
        MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

        QStackedWidget* stack_;
        Setting* settingsPtr_;
        Battle* battlePtr_;
        BattleSetting* battleSettingPtr_;
};
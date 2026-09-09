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

/// @brief Application root widget: owns the widget holding every top-level screen and the
/// app-wide Setting/Battle/BattleSetting state shared across them.
class MainWidget : public QWidget{
    Q_OBJECT
    public slots:
        /// @brief Switches the visible screen in stack_ to target. Connected to every
        /// BaseScreenWidget::screenChanged signal.
        /// @param target screen to switch to.
        void switchScreen(Screen target);

    public:
        /// @param parent optional Qt parent widget.
        MainWidget(QWidget *parent = nullptr);
        ~MainWidget();

        QStackedWidget* stack_;
        Setting* settingsPtr_;
        Battle* battlePtr_;
        BattleSetting* battleSettingPtr_;
};
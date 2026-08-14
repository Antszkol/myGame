#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "baseScreenWidget.hpp"
#include "battleWidget.hpp"
#include "battleSettingsWidget.hpp"

battleWidget::battleWidget(battleSetting* battleSettingPtr){
    this->battleSettingPtr = battleSettingPtr;
    QFont font("Garamond", 16);
    this->setFont(font);

    QPushButton* battleButton = new QPushButton("Start Battle!", this);
    QPushButton* battleSettingsButton = new QPushButton("Battle Settings", this);
    QPushButton* backButton = new QPushButton("Back", this);

    connect(backButton, &QPushButton::clicked, this, [this](){navigateTo(Screen::menu);});
    connect(battleSettingsButton, &QPushButton::clicked, this, [this](){
        battleSettingsWidget* dialog = new battleSettingsWidget(this->battleSettingPtr, this);
        dialog->exec();
    });

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(battleButton);
    layout->addWidget(battleSettingsButton);
    layout->addWidget(backButton);
}

battleWidget::~battleWidget(){}
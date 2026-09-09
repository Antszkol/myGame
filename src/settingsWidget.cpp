#include <QFormLayout>
#include <QString>
#include <algorithm>
#include "settingsWidget.hpp"

SettingsWidget::SettingsWidget(Setting* settingsPtr, QWidget* parent) : QDialog(parent){
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->settingsPtr_ = settingsPtr;
    resolutions_ = settingsPtr->getAvailableResolutions();

    windowSizeComboBox_ = new QComboBox(this);
    for(const auto& res : resolutions_){
        windowSizeComboBox_->addItem(QString("%1x%2").arg(res.first).arg(res.second));
    }

    auto currentSize = settingsPtr->getWindowSize();
    auto it = std::find(resolutions_.begin(), resolutions_.end(), currentSize);
    if(it != resolutions_.end()){
        windowSizeComboBox_->setCurrentIndex(std::distance(resolutions_.begin(), it));
    }

    saveButton_ = new QPushButton("Save Settings", this);
    connect(saveButton_, &QPushButton::clicked, this, &SettingsWidget::onSaveClicked);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Resolution:", windowSizeComboBox_);
    layout->addRow(saveButton_);
}

SettingsWidget::~SettingsWidget(){}

void SettingsWidget::onSaveClicked(){
    pair<int,int> newSize = resolutions_[windowSizeComboBox_->currentIndex()];
    this->settingsPtr_->saveSettings(newSize);

    QWidget* mainWindow = this->parentWidget()->window();
    mainWindow->setFixedSize(newSize.first, newSize.second);

    accept();
}

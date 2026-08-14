#include <QFormLayout>
#include <QString>
#include <algorithm>
#include "settingsWidget.hpp"

settingsWidget::settingsWidget(setting* settingsPtr, QWidget* parent) : QDialog(parent){
    this->settingsPtr = settingsPtr;
    resolutions = settingsPtr->getAvailableResolutions();

    brightnessSpinBox = new QSpinBox(this);
    brightnessSpinBox->setRange(0, 100);
    brightnessSpinBox->setValue(settingsPtr->getBrightness());

    windowSizeComboBox = new QComboBox(this);
    for(const auto& res : resolutions){
        windowSizeComboBox->addItem(QString("%1x%2").arg(res.first).arg(res.second));
    }

    auto currentSize = settingsPtr->getWindowSize();
    auto it = std::find(resolutions.begin(), resolutions.end(), currentSize);
    if(it != resolutions.end()){
        windowSizeComboBox->setCurrentIndex(std::distance(resolutions.begin(), it));
    }

    saveButton = new QPushButton("Save Settings", this);
    connect(saveButton, &QPushButton::clicked, this, &settingsWidget::onSaveClicked);

    QFormLayout* layout = new QFormLayout(this);
    layout->addRow("Brightness:", brightnessSpinBox);
    layout->addRow("Resolution:", windowSizeComboBox);
    layout->addRow(saveButton);
}

settingsWidget::~settingsWidget(){}

void settingsWidget::onSaveClicked(){
    pair<int,int> newSize = resolutions[windowSizeComboBox->currentIndex()];
    this->settingsPtr->saveSettings(brightnessSpinBox->value(), newSize);

    QWidget* mainWindow = this->parentWidget()->window();
    mainWindow->setFixedSize(newSize.first, newSize.second);

    accept();
}

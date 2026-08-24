#include "baseScreenWidget.hpp"

BaseScreenWidget::BaseScreenWidget() : QWidget(){}

void BaseScreenWidget::navigateTo(Screen target)
{
    emit screenChanged(target);
}
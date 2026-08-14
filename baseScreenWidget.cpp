#include "baseScreenWidget.hpp"

baseScreenWidget::baseScreenWidget() : QWidget(){}

void baseScreenWidget::navigateTo(Screen target)
{
    emit screenChanged(target);
}
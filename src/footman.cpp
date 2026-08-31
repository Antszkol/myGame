#include "footman.hpp"

Footman::Footman(UnitWidget* unitWidgetPtr) : Unit(footman, UnitStatsMap.at(footman), unitWidgetPtr), armour_(30) {}

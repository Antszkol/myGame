#pragma once
#include "unitType.hpp"
#include "unitStats.hpp"

class Unit {
    public:
        Unit(const UnitStats& unitStats);

    protected:
        const UnitStats unitStats_;  
};
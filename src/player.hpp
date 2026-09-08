#pragma once
#include "unit.hpp"
#include "playerStats.hpp"
#include <vector>

class Player {
    public:
        Player(int playerIdx, int startColumn, bool isAI, int startGold);

        void subtractGold(int minus);
        void refreshUnitsSpeed();
        void addUnit(Unit* unitPtr);
        void removeUnit(Unit* unitPtr);
        void addCasualty();
        void addFrag();
        void addDamageDealt(int damage);
        void addDamageReceived(int damage);

        bool isAI();
        int getGold();
        int getPlayerIdx() const;
        int getPlayerStartColumn() const;
        const std::vector<Unit*>& getUnits() const;
        const PlayerStats& getPlayerStats() const;

    private:
        std::vector<Unit*> units_;
        int gold_;
        int playerIdx_;
        bool isAI_;
        
        const int startColumn_;
        PlayerStats playerStats_;
    };
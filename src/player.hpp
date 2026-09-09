#pragma once
#include "unit.hpp"
#include "playerStats.hpp"
#include <vector>

/// @brief One side of a battle: owns gold, deployed units, and running PlayerStats.
class Player {
    public:
        /// @param playerIdx 1 or 2, identifies this player.
        /// @param startColumn map column defining this player's deployment zone.
        /// @param isAI whether this player's turns are driven by AIHandler.
        /// @param startGold starting gold, from BattleSetting.
        Player(int playerIdx, int startColumn, bool isAI, int startGold);

        /// @param minus gold to deduct (e.g. unit recruitment cost).
        void subtractGold(int minus);

        /// @brief Resets every owned unit's remaining speed and attacked-this-turn flag; called
        /// at the start of this player's turn.
        void refreshUnitsSpeed();

        /// @param unitPtr unit to add to this player's roster; also increments recruitedUnitsCount_.
        void addUnit(Unit* unitPtr);

        /// @param unitPtr unit to remove from the player (e.g. on death).
        void removeUnit(Unit* unitPtr);

        /// @brief Increments this player's casualty count (an owned unit died).
        void addCasualty();

        /// @brief Increments this player's frag count (this player killed an enemy unit).
        void addFrag();

        /// @param damage amount to add to this player's total damage dealt stat.
        void addDamageDealt(int damage);

        /// @param damage amount to add to this player's total damage received stat.
        void addDamageReceived(int damage);

        /// @return whether this player's turns are driven by AIHandler.
        bool isAI();

        /// @return current gold.
        int getGold();

        /// @return this player's index (1 or 2).
        int getPlayerIdx() const;

        /// @return the map column defining this player's deployment zone.
        int getPlayerStartColumn() const;

        /// @return every unit currently owned by this player.
        const std::vector<Unit*>& getUnits() const;

        /// @return this player's running battle statistics.
        const PlayerStats& getPlayerStats() const;

    private:
        std::vector<Unit*> units_;
        int gold_;
        int playerIdx_;
        bool isAI_;
        
        const int startColumn_;
        PlayerStats playerStats_;
    };
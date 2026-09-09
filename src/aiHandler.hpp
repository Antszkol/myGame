#pragma once
#include <vector>
#include <map>

#include "player.hpp"
#include "map.hpp"
#include "mapHandler.hpp"
#include "turnHandler.hpp"

/// @brief Drives one player's turn automatically with a simple heuristic strategy: deploy near
/// the enemy deployment zone, attack any enemy in range, otherwise move toward the enemy deployment zone.
/// If didn't attack before movement - attack after it.
class AIHandler {
    public:
        /// @param map the battle map.
        /// @param playerPtr the AI-controlled player.
        /// @param turnHandlerPtr turn handler to issue deploy/move/attack/end-turn actions through.
        /// @param mapHandlerPtr map handler, used for pathfinding/target queries and widget lookup.
        AIHandler(Map& map, Player* playerPtr, TurnHandler* turnHandlerPtr, MapHandler* mapHandlerPtr);

        /// @brief Runs this AI's whole turn: deploys new units near the front, attacks any unit
        /// already in range, moves each remaining unit toward the enemy, then attacks again and
        /// ends the turn. Pauses briefly (see waitMs) between actions so they're visible on screen.
        void executeTurn();

        /// @param tilePtr tile to search reachable destinations from.
        /// @param range maximum movement points to spend.
        /// @return reachable tiles within range mapped to their BFS distance to the nearest
        /// enemy deployment-zone tile (lower is closer to the enemy).
        std::map<Tile*, int> getDistanceToEnemy(Tile* tilePtr, int range);

    private:
        /// @brief Blocks for milliseconds without freezing the Qt event loop (via QEventLoop +
        /// QTimer::singleShot), so the GUI stays responsive between AI actions.
        void waitMs(int milliseconds);

        Player* playerPtr_;
        TurnHandler* turnHandlerPtr_;
        MapHandler* mapHandlerPtr_;
        Map& map_;
};
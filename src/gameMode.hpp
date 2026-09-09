#pragma once
#include <map>
#include <string>

/// @brief Who controls Player 2 for the duration of a battle.
enum class GameMode{
    HotSeat, ///< Both players are controlled by humans, taking turns on the same machine.
    VsAI,    ///< Player 2 is controlled by AIHandler.
};

/// @brief Human-readable label for each GameMode, used in the UI.
inline std::map<GameMode, std::string> GameModeMap = {
    {GameMode::HotSeat, "Hot-seat"},
    {GameMode::VsAI, "Versus AI"}
};

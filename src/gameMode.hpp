#pragma once
#include <map>
#include <string>

enum class GameMode{
    HotSeat,
    VsAI,
};

inline std::map<GameMode, std::string> GameModeMap = {
    {GameMode::HotSeat, "Hot-seat"},
    {GameMode::VsAI, "Versus AI"}
};

#pragma once
#include <map>
#include <string>

/// @brief The action the current player is in the middle of performing during their turn.
enum class ActionMode{
    None,
    RecruitUnit,
    AttackUnit,
    MoveUnit,
};

/// @brief Human-readable label for each ActionMode, used in the UI.
inline std::map<ActionMode, std::string> ActionModeMap = {
    {ActionMode::RecruitUnit, "Recruit unit"},
    {ActionMode::AttackUnit, "Attack unit"},
    {ActionMode::MoveUnit, "Move unit"}
};
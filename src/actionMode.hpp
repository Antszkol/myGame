#pragma once
#include <map>
#include <string>

enum class ActionMode{
    None,
    RecruitUnit,
    AttackUnit,
    MoveUnit,
};

inline std::map<ActionMode, std::string> ActionModeMap = {
    {ActionMode::RecruitUnit, "Recruit unit"},
    {ActionMode::AttackUnit, "Attack unit"},
    {ActionMode::MoveUnit, "Move unit"}
};
#pragma once

/// @brief Running battle statistics for one Player, shown on the result screen.
struct PlayerStats {
    int fragCount_ = 0;           ///< Enemy units killed.
    int casualtyCount_ = 0;       ///< Own units lost.
    int recruitedUnitsCount_ = 0; ///< Units recruited over the whole battle.
    int damageReceived_ = 0;      ///< Total damage taken by this player's units.
    int damageDealt_ = 0;         ///< Total damage dealt by this player's units.
};
# myGame — Turn-Based Tactics in the Spirit of Heroes of Might and Magic

A turn-based strategy/tactics game built with C++ and Qt, developed as a semester project at Warsaw University of Technology.

## Problem

The goal was to design and implement a turn-based tactical battle system inspired by *Heroes of Might and Magic* — players recruit units, manage a roster, and resolve battles turn by turn on a grid, with a full menu and settings layer around the core gameplay loop.

Beyond the gameplay logic itself, the project doubled as an exercise in object-oriented architecture: designing a class hierarchy and a set of collaborating systems (turn/state management, map/pathfinding, rendering) that stays clean as features get added, rather than one that has to be reworked with every new mechanic.

## Status

The core gameplay loop is playable end to end: main menu → battle setup → recruit units into per-player deployment zones → move and attack across turns → win by attrition (units die and are removed). There is no separate rendering layer (no `MainRenderer`/`GUIRenderer`) — screens are plain Qt widgets that lay themselves out and paint through normal Qt/QGraphicsView mechanisms.

Not yet implemented: AI, settings/battle-settings persistence to disk (values are in-memory only), and any "one action per turn" cap on movement (movement is intentionally budget-based via unit speed, not capped to a single move — see `Notes.md`).

## Architecture

**Screen shell & navigation:**

- **`MainWidget`** — the top-level window. Owns a `QStackedWidget` holding every screen, owns the `Setting`/`BattleSetting` instances, and switches pages via the `switchScreen(Screen)` slot.
- **`BaseScreenWidget`** — common base class for full-page screens. Declares a `screenChanged(Screen)` signal and a `navigateTo(Screen)` slot, so a screen can ask to switch pages without knowing about the stack itself.
- **`MenuWidget`, `BattleMenuWidget`** — concrete screens derived from `BaseScreenWidget`. `BattleMenuWidget` is the pre-battle menu (start battle / battle settings / back) and owns the `createBattle()` slot that builds a `Map` + `Battle` and hands them to `BattleWidget` via the `battleCreated` signal.
- **`SettingsWidget`, `BattleSettingsWidget`** — `QDialog` subclasses that edit general/battle settings and write the results back through `Setting`/`BattleSetting` setters.
- **`Setting`, `BattleSetting`** — plain data holders (getters/setters) for configurable values (brightness, window size, starting gold, max unit count). In-memory only; no file persistence yet.

**Battle screen & turn logic:**

- **`BattleWidget`** — the in-battle screen. Hosts `ShopWidget`, `ActionWidget`, and `MapWidget`. `setBattle(Battle*, BattleSetting*)` is where `TurnHandler` and `MapWidget` actually get constructed, once a `Battle`/`Map` exist (both need the map's size up front — `TurnHandler` for player deployment columns, `MapWidget` for the tile grid).
- **`TurnHandler`** — owns the two `Player`s, the current player, and `ActionMode` (None/RecruitUnit/MoveUnit/AttackUnit). Implements the actual game actions: `confirmUnitDeployment`, `moveUnit`, `attackUnit`, `endTurn` (switches player, refreshes the new current player's units — speed and the "already attacked" flag — and clears the map's selection state).
- **`ActionWidget`** — the in-battle action bar (Move unit / Attack unit / End turn buttons), emits request signals that `TurnHandler` listens to.
- **`ShopWidget`** — unit-recruitment UI; emits `unitPurchaseRequested(UnitType)`.
- **`Player`** — per-player state: gold, owned `Unit`s, and a deployment `startColumn_` (player 1 spawns near column 0, player 2 near the last column).

**Map, placement & rendering:**

- **`MapWidget`** (`QGraphicsView`) — owns the `QGraphicsScene`, builds the `TileWidget` grid, and handles all mouse input (`onTileHovered`/`onTileLeft`/`onTileClicked`) and tile painting (`paintTile`, `restoreTileColor`). It drives a `MapHandler` for anything that isn't "put a color on a tile."
- **`MapHandler`** — owns *where things are*: the reachability/targeting queries (`findMovePaths`/`findTargets`, backed internally by `Finder`), the tile-widget lookup table, and the current selection state (which unit is selected, which tile it started from, which tiles/targets are currently highlighted) as pure data — no painting.
- **`Finder`** — BFS/Dijkstra-style reachability. `findMovePaths` respects both a unit's remaining speed and `Tile::isPassable()` (impassable tiles, e.g. water, are excluded from the search graph entirely, not just visually). `FindTargets` finds enemy-occupied tiles within a unit's attack range.
- **`Map`, `Tile`, `TileWidget`** — the grid model (`Map` holds all `Tile`s and neighbour lookups) and its `QGraphicsRectItem` visual (`TileWidget`). `Tile::isWithinDeploymentZone(Player*)` gates recruitment to columns near a player's spawn.
- **`Unit`, `UnitWidget`, `Player`** — `Unit` holds mutable per-battle state (`remainingSpeed_`, `remainingHealth_`, `hasAttacked_`) separate from the immutable `UnitStats` table, plus its owning `Player` (`ownerPtr_`, used to filter valid move/attack targets to the current player's own units and enemy units respectively). `UnitWidget` (`QGraphicsPixmapItem`, parented to its current `TileWidget`) renders a sprite (from `img/`, per unit type and owning player) and a live health label; on death it swaps to a "dead" sprite and is removed a moment later via `QTimer::singleShot` rather than immediately, so the death is actually visible. `Unit` and `UnitWidget` have a circular construction dependency (each needs the other) resolved by constructing `Unit` first with no widget, then the `UnitWidget`, then patching `Unit::setUnitWidgetPtr(...)`.

## Requirements

- Qt5 (`Widgets` module)
- C++20
- CMake 3.16+

## Building

```bash
git clone <repo-url>
cd myGame
mkdir build && cd build
cmake ..
make
```

`CMAKE_AUTOMOC`/`AUTOUIC`/`AUTORCC` are enabled, so Qt's moc/uic/rcc steps run automatically — no manual wrapping needed for new widgets. The binary (`build/myGame`) expects to be run from `build/` — it loads unit sprites via the relative path `../img/...`.

## Repo structure

All source lives flat under `src/`; `CMakeLists.txt` sits at the repo root and lists every `.cpp` explicitly (no globbing).

```
.
├── CMakeLists.txt
├── README.md
├── Notes.md
├── img                                    # unit sprites (PNG), loaded at runtime
└── src
    ├── game.cpp                             # entry point
    ├── mainWidget.cpp / .hpp                # top-level window, owns the QStackedWidget screen stack
    ├── baseScreenWidget.cpp / .hpp          # shared base for full-page screens
    ├── screen.hpp                            # Screen enum used for navigation
    │
    ├── menuWidget.cpp / .hpp                # main menu screen
    ├── battleMenuWidget.cpp / .hpp          # pre-battle menu screen (creates the Battle)
    ├── settingsWidget.cpp / .hpp            # QDialog for general settings
    ├── battleSettingsWidget.cpp / .hpp      # QDialog for battle settings
    ├── settings.cpp / .hpp                  # general settings data holder
    ├── battleSettings.cpp / .hpp            # battle-specific settings data holder
    │
    ├── battle.cpp / .hpp                    # owns a Map + BattleSetting for one battle
    ├── battleWidget.cpp / .hpp              # in-battle screen: hosts MapWidget, ActionWidget, ShopWidget
    ├── turnHandler.cpp / .hpp               # turn/player state machine, action mode, move/attack/deploy
    ├── actionWidget.cpp / .hpp              # in-battle action bar (end turn, move unit, attack unit)
    ├── actionMode.hpp                        # ActionMode enum (None/RecruitUnit/AttackUnit/MoveUnit)
    ├── shopWidget.cpp / .hpp                # unit-recruitment shop UI
    ├── player.cpp / .hpp                    # per-player state (gold, units, deployment column)
    │
    ├── map.cpp / .hpp                       # tile grid, neighbour lookup
    ├── mapWidget.cpp / .hpp                 # QGraphicsView: rendering + mouse input
    ├── mapHandler.cpp / .hpp                # placement/selection state + pathfinding queries
    ├── mapTiles.hpp                          # hardcoded tile-layout presets (river, bog)
    ├── mapType.hpp                            # mapType enum (which preset to load)
    ├── tile.cpp / .hpp                      # single grid cell: type, occupant, deployment zone check
    ├── tileType.hpp                          # TileType enum (grass/water/mud/barricade)
    ├── tileWidget.cpp / .hpp                # QGraphicsRectItem for one tile
    ├── finder.cpp / .hpp                    # BFS reachability (movement) + targeting (attack range)
    │
    ├── unit.cpp / .hpp                      # unit stats/state (speed, health, hasAttacked, owner)
    ├── unitStats.hpp                         # UnitStats struct + per-UnitType stat table
    ├── unitType.hpp                          # UnitType enum
    └── unitWidget.cpp / .hpp                # QGraphicsPixmapItem for one unit: sprite + health label
```

Class names use PascalCase (`MainWidget`, `TurnHandler`, `UnitWidget`, ...); member variables use camelCase with a trailing underscore (`settingsPtr_`, `unitSelected_`, ...). Methods within a class are ordered general/action methods first, then setters (`setXxx`), then getters (`getXxx`) last, in both the header and the source file.

## Author

Antoni Biskupski — Warsaw University of Technology, Automation, Robotics and Industrial Computer Science

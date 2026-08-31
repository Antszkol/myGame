# myGame — Turn-Based Tactics in the Spirit of Heroes of Might and Magic

A turn-based strategy/tactics game built with C++ and Qt, developed as a semester project at Warsaw University of Technology.

## Problem

The goal was to design and implement a turn-based tactical battle system inspired by *Heroes of Might and Magic* — players recruit units, manage a roster, and resolve battles turn by turn on a grid, with a full menu and settings layer around the core gameplay loop.

Beyond the gameplay logic itself, the project doubled as an exercise in object-oriented architecture: designing a class hierarchy (abstract `Unit` base with concrete subclasses, composition vs. aggregation vs. association between core systems) that stays clean as features get added, rather than one that has to be reworked with every new mechanic.

## Architecture

The full intended design is sketched in `materials/diagram.webp`, but only part of it is implemented so far. There is no separate rendering layer (no `MainRenderer`/`GUIRenderer`/`MapRenderer`/`MenuRenderer`) — screens are plain Qt widgets that lay themselves out and paint through normal Qt mechanisms.

**Implemented — screen shell & navigation:**

- **`MainWidget`** — the top-level window. Owns a `QStackedWidget` holding every screen, owns the `Setting`/`BattleSetting` instances, and switches pages via the `switchScreen(Screen)` slot.
- **`BaseScreenWidget`** — common base class for full-page screens. Declares a `screenChanged(Screen)` signal and a `navigateTo(Screen)` slot, so a screen can ask to switch pages without knowing about the stack itself.
- **`MenuWidget`, `BattleMenuWidget`** — concrete screens derived from `BaseScreenWidget`, each building its own buttons/layout directly and opening a modal settings dialog. `BattleMenuWidget` is the pre-battle menu (start battle / battle settings / back) — the screen for an actual in-progress battle doesn't exist yet.
- **`SettingsWidget`, `BattleSettingsWidget`** — `QDialog` subclasses that edit general/battle settings and write the results back through `Setting`/`BattleSetting` setters.
- **`Setting`, `BattleSetting`** — plain data holders (getters/setters) for configurable values (brightness, window size, starting gold, max unit count). Currently in-memory only; no file persistence is wired up yet despite the unused `path_` member on `Setting`.

**Not yet implemented (planned per the class diagram):**

- **Game / Map** — `Game` is currently an near-empty placeholder that just owns a `Setting` instance; `createBattle()` is stubbed out and commented. `Map`/`Tile`/`MapWidget` are in the CMake build now, but are early, unfinished sketches — `map.cpp` still has a syntax error (missing semicolon) and won't compile as-is.
- **Players & units** — `Player`, `Hero`, `Barracks`, and the `Unit` hierarchy (`Warrior`/`Archer`/`Mage` extending an abstract `Unit`) from the diagram have no corresponding code yet.
- **Turns & battle** — `Battle`, `TurnHandler`, `Move`, and the `Skill` hierarchy are design-only so far.
- **AI** — `AIHandler` is design-only; no AI move computation exists yet.

## Status

Currently working: main menu, battle screen shell, battle settings, and general settings — navigation and the settings dialogs are wired up through the GUI (values are held in memory, not yet persisted to disk). Core battle logic and AI are not implemented yet, and the map/tile model is early enough that the project doesn't currently build (`map.cpp` has a syntax error).

## Requirements

- Qt5 (`Widgets` module)
- C++17 or later
- CMake 3.16+

## Building

```bash
git clone <repo-url>
cd myGame
mkdir build && cd build
cmake ..
cmake --build .
```

`CMAKE_AUTOMOC`/`AUTOUIC`/`AUTORCC` are enabled, so Qt's moc/uic/rcc steps run automatically — no manual wrapping needed for new widgets.

## Repo structure

All source lives flat under `src/`; `CMakeLists.txt` sits at the repo root and lists every `.cpp` explicitly (no globbing).

```
.
├── CMakeLists.txt
├── README.md
├── Notes.md
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
    ├── turnHandler.cpp / .hpp               # turn/player state machine, action mode, recruit/move dispatch
    ├── actionWidget.cpp / .hpp              # in-battle action bar (end turn, move unit, ...)
    ├── actionMode.hpp                        # ActionMode enum (None/RecruitUnit/AttackUnit/MoveUnit)
    ├── shopWidget.cpp / .hpp                # unit-recruitment shop UI
    ├── player.cpp / .hpp                    # per-player state (gold, ...)
    │
    ├── map.cpp / .hpp                       # tile grid, neighbour lookup
    ├── mapWidget.cpp / .hpp                 # QGraphicsView rendering the map, tile hover/click handling
    ├── mapTiles.hpp                          # hardcoded tile-layout presets (river, bog)
    ├── mapType.hpp                            # mapType enum (which preset to load)
    ├── tile.cpp / .hpp                      # single grid cell: type, occupant, walkability
    ├── tileType.hpp                          # TileType enum (grass/water/mud/barricade)
    ├── tileWidget.cpp / .hpp                # QGraphicsItem for one tile
    ├── finder.cpp / .hpp                    # pathfinding: reachable tiles within a unit's speed
    │
    ├── unit.cpp / .hpp                      # base unit: stats + linked UnitWidget
    ├── unitStats.hpp                         # UnitStats struct + per-UnitType stat table
    ├── unitType.hpp                          # UnitType enum
    ├── unitWidget.cpp / .hpp                # QGraphicsItem for one unit, parented to its TileWidget
    └── footman.cpp / .hpp                   # footman-specific Unit subclass
```

Class names use PascalCase (`MainWidget`, `TurnHandler`, `UnitWidget`, ...); member variables use camelCase with a trailing underscore (`settingsPtr_`, `unitSelected_`, ...).

## Author

Antoni Biskupski — Warsaw University of Technology, Automation, Robotics and Industrial Computer Science

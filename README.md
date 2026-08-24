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

```
.
├── game.cpp
├── mainWidget.cpp               # top-level window, screen stack
├── baseScreenWidget.cpp         # shared base for the screen widgets below
├── menuWidget.cpp
├── battleMenuWidget.cpp          # pre-battle menu screen
├── battleSettingsWidget.cpp     # QDialog for battle settings
├── settingsWidget.cpp           # QDialog for general settings
├── settings.cpp                 # general settings data holder
├── battleSettings.cpp           # battle-specific settings data holder
├── screen.hpp                   # Screen enum used for navigation
├── map.cpp / tile.cpp / mapWidget.cpp   # early, unfinished battle-grid sketches
├── materials/diagram.webp       # target class diagram for the full design
├── CMakeLists.txt
└── README.md
```

Note: `map.cpp` currently has a syntax error and won't compile — the build is broken until that's fixed. Class names throughout the codebase use PascalCase (`MainWidget`, `Setting`, `BattleSetting`, ...); member variables use camelCase with a trailing underscore (`settingsPtr_`, `startGold_`, ...).

## Author

Antoni Biskupski — Warsaw University of Technology, Automation, Robotics and Industrial Computer Science

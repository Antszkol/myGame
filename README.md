# myGame — Turn-Based Tactics in the Spirit of Heroes of Might and Magic

A turn-based strategy/tactics game built with C++ and Qt, developed as a semester project at Warsaw University of Technology.

## Problem

The goal was to design and implement a turn-based tactical battle system inspired by *Heroes of Might and Magic* — players recruit units, manage a roster, and resolve battles turn by turn on a grid, with a full menu and settings layer around the core gameplay loop.

Beyond the gameplay logic itself, the project doubled as an exercise in object-oriented architecture: designing a class hierarchy (abstract `Unit` base with concrete subclasses, composition vs. aggregation vs. association between core systems) that stays clean as features get added, rather than one that has to be reworked with every new mechanic.

## Architecture

The system is split into a few cooperating areas:

- **Game / Map** — `Game` orchestrates the session; `Map` owns a grid of `Tile`s (composition).
- **Players & units** — `Player` composes a `Hero` and aggregates `Unit`s recruited through `Barracks`. `Unit` is an abstract base class with `Warrior`, `Archer`, and `Mage` subclasses, each overriding shared virtual behavior (movement range, attack logic).
- **Turns & battle** — `Battle` drives combat; `TurnHandler` manages turn order and delegates the current player's action to a `Move` object, keeping per-turn logic out of the turn-order bookkeeping.
- **Rendering** — `MainRenderer` coordinates sub-renderers (`GUIRenderer`, `MapRenderer`, `MenuRenderer`), each responsible for one layer of the screen (HUD/selection state, the battle grid, menus).
- **AI** — `AIHandler` computes moves for non-human players against the same `Move`/`TurnHandler` interface used by human input.
- **Settings** — `Settings` and a dedicated battle-settings widget expose configurable parameters (e.g. board/window sizing, brightness) through the Qt GUI rather than hardcoding them.

## Status

Currently working: main menu, battle settings screen, and general settings — all wired up and saving/loading correctly through the GUI. Core battle logic and AI are in progress.

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
├── mainWidget.cpp
├── baseScreenWidget.cpp        # shared base for the screen widgets below
├── menuWidget.cpp
├── battleWidget.cpp
├── battleSettingsWidget.cpp
├── settingsWidget.cpp
├── settings.cpp                # settings persistence
├── battleSettings.cpp          # battle-specific settings persistence
├── CMakeLists.txt
└── README.md
```

## Author

Antoni Biskupski — Warsaw University of Technology, Automation, Robotics and Industrial Computer Science

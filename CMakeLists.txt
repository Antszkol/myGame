cmake_minimum_required(VERSION 3.16)
project(myGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(myGame
    src/game.cpp
    src/battle.cpp
    src/mainWidget.cpp
    src/menuWidget.cpp
    src/battleWidget.cpp
    src/battleMenuWidget.cpp
    src/baseScreenWidget.cpp
    src/battleSettingsWidget.cpp
    src/settingsWidget.cpp
    src/settings.cpp
    src/battleSettings.cpp
    src/tile.cpp
    src/map.cpp
    src/mapWidget.cpp
    src/mapHandler.cpp
    src/tileWidget.cpp
    src/shopWidget.cpp
    src/unit.cpp
    src/unitWidget.cpp
    src/turnHandler.cpp
    src/player.cpp
    src/actionWidget.cpp
    src/finder.cpp
    src/logger.cpp
    src/moveMessage.cpp
    src/attackMessage.cpp
    src/killMessage.cpp
    src/recruitMessage.cpp
    src/resultWidget.cpp
    src/aiHandler.cpp
)

target_include_directories(myGame PRIVATE src)
target_link_libraries(myGame PRIVATE Qt5::Widgets)

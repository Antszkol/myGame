cmake_minimum_required(VERSION 3.16)
project(myGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(nlohmann_json 3.11 REQUIRED)

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
    src/tileWidget.cpp
    src/mapWidget.cpp
    src/shopWidget.cpp
    src/unit.cpp
    src/unitWidget.cpp
    src/footman.cpp
    src/turnHandler.cpp
    src/player.cpp
)

target_include_directories(myGame PRIVATE src)
target_link_libraries(myGame PRIVATE Qt5::Widgets)

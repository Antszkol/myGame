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
    game.cpp
    mainWidget.cpp
    menuWidget.cpp
    battleWidget.cpp
    baseScreenWidget.cpp
    battleSettingsWidget.cpp
    settingsWidget.cpp
    settings.cpp
    battleSettings.cpp
)

target_link_libraries(myGame PRIVATE Qt5::Widgets nlohmann_json::nlohmann_json)

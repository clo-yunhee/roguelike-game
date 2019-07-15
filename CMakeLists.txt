cmake_minimum_required(VERSION 3.14)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI REQUIRED)

add_executable(Roguelike src/main.cpp src/macros.h src/LauncherWindow.cpp src/LauncherWindow.h src/GameWindow.cpp src/GameWindow.h src/Screen.h src/Screen.cpp src/screens/MainMenu.cpp src/screens/MainMenu.cpp)
target_link_libraries(Roguelike sfml-graphics sfml-audio tgui)

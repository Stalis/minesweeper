cmake_minimum_required(VERSION 3.15)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "--debug -Wall -Wpedantic")

set(CURSES_LIB "")
set(CURSES_INCLUDE "")


add_executable(minesweeper main.cpp
        src/Map/Cell.hpp
        src/Map/Map.hpp src/Map/Map.cpp
        src/Map/Coordinate.hpp
        src/View/ConsoleGameView.cpp src/View/ConsoleGameView.hpp
        src/View/IGameView.hpp
        src/Game.cpp src/Game.hpp
        src/Map/IMap.hpp
        src/Map/IMapFactory.cpp
        src/Map/IMapFactory.hpp
        src/Command.hpp
        src/ViewModel/CellInfo.hpp
        src/ViewModel/GameViewModel.cpp src/ViewModel/GameViewModel.hpp
        src/ViewModel/IGameViewModel.hpp
        src/Vector2.hpp
        src/GameState.hpp src/View/CursesGameView.cpp src/View/CursesGameView.hpp)

#======= INCLUDING CURSES ========#

if (WIN32 OR MSVC)
    add_subdirectory(lib)
    target_include_directories(minesweeper PRIVATE lib/PDCurses)
    target_link_libraries(minesweeper PRIVATE PDCurses)
else ()
    set(CURSES_NEED_NCURSES TRUE)
    find_package(Curses)
    if (CURSES_FOUND)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CURSES_CFLAGS}")
        target_include_directories(minesweeper PRIVATE ${CURSES_INCLUDE_DIRS})
        target_link_libraries(minesweeper ${CURSES_LIBRARIES})
    endif ()
endif ()

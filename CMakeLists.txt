cmake_minimum_required(VERSION 3.12)
project(minesweeper)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/Wall /Od /utf-8 /Zi /wd4514")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "--debug -Wall -Wpedantic")
endif ()

set(SOURCES
        src/Map/IMap.hpp
        src/Map/IMapFactory.hpp src/Map/IMapFactory.cpp
        src/Map/Cell.hpp
        src/Map/Coordinate.hpp
        src/Map/Map.hpp src/Map/Map.cpp

        src/View/IGameView.hpp
        src/View/ConsoleColors.hpp
        src/View/ConsoleGameView.cpp src/View/ConsoleGameView.hpp

        src/Model/CellInfo.hpp
        src/Game.cpp src/Game.hpp
        src/Command.hpp src/Command.cpp
        src/Vector2.hpp
        src/GameState.hpp
        src/Utils.hpp

        src/Model/IGameModel.hpp
        src/Model/GameModel.cpp src/Model/GameModel.hpp

        src/Controller/IController.hpp
        src/Controller/TextCommandController.cpp src/Controller/TextCommandController.hpp)

if (WITH_CURSES)
    set(SOURCES
            ${SOURCES}
            src/View/CursesGameView.cpp src/View/CursesGameView.hpp
            )
endif ()

add_executable(minesweeper main.cpp ${SOURCES})

target_include_directories(minesweeper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (WITH_CURSES)
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
endif ()
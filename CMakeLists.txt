cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "--debug -Wall -Wpedantic")

add_executable(untitled main.cpp
        src/Map/Cell.hpp
        src/Map/Map.hpp src/Map/Map.cpp
        src/Map/Coordinate.hpp src/View/ConsoleGameView.cpp src/View/ConsoleGameView.hpp src/View/IGameView.hpp src/Game.cpp src/Game.hpp src/Map/IMap.hpp src/Map/IMapFactory.cpp src/Map/IMapFactory.hpp src/Command.hpp src/ViewModel/CellInfo.hpp src/ViewModel/GameViewModel.cpp src/ViewModel/GameViewModel.hpp src/ViewModel/IGameViewModel.hpp src/Vector2.hpp src/GameState.hpp)
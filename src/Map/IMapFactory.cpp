//
// Created by Stanislav on 19/10/2019.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include "IMapFactory.hpp"
#include "Map.hpp"

IMap* IMapFactory::CreateMap(int minesCount) {
    return CreateMap(minesCount, DEFAULT_RANDOM_WINDOW);
}

IMap* IMapFactory::CreateMap(int mineCount, int randWindow) {
    return CreateMap(mineCount, randWindow, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

IMap* IMapFactory::CreateMap(int mineCount, int width, int height) {
    return CreateMap(mineCount, DEFAULT_RANDOM_WINDOW, width, height);
}

IMap* IMapFactory::CreateMap(int mineCount, int randWindow, int width, int height) {
    /// ========== START ASSERTIONS =========== ///
    // Randomize assertions
    if (randWindow > RANDOM_MAX || randWindow < 0) {
        std::string str("[Map::CreateMap] Invalid random window: ");
        str.append(std::to_string(randWindow));
        throw std::runtime_error(str);
    }
    // Size assertion
    if (width < 0 || height < 0) {
        std::string str("[Map::CreateMap] Invalid map size: ");
        str.append(std::to_string(width));
        str.append(" x ");
        str.append(std::to_string(height));
        throw std::runtime_error(str);
    }
    /// ========== END ASSERTIONS =========== ///

    auto* instance = new Map(width, height);
    auto cells = &instance->_cells;
    /// ========== Initialize C++11 randomizer =========== ///
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, RANDOM_MAX);

    int currentMineCount = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto coord = Coordinate(x, y);
            bool isMine = false;

            if (currentMineCount < mineCount) {
                if (dist(mt) >= randWindow) {
                    isMine = true;
                    currentMineCount++;
                }
            }
            cells->insert(std::pair<Coordinate, Cell>(coord, Cell(isMine)));
        }
    }

    for (auto& item : *cells) {
        std::cout << "{" << item.first.x << "; " << item.first.y << "} " << item.second.hasMine() << std::endl << std::flush;
    }

    return instance;
}


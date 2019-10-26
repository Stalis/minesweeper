//
// Created by Stanislav on 19/10/2019.
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include "IMapFactory.hpp"
#include "Map.hpp"

static std::unique_ptr<std::vector<Coordinate>> generateMines(int count, int width, int height);
static inline bool hasMine(std::vector<Coordinate>& vec, Coordinate coord);

std::shared_ptr<IMap> IMapFactory::CreateMap(int minesCount) {
    return CreateMap(minesCount, DEFAULT_RANDOM_WINDOW);
}

std::shared_ptr<IMap>IMapFactory::CreateMap(int mineCount, int randWindow) {
    return CreateMap(mineCount, randWindow, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

std::shared_ptr<IMap>IMapFactory::CreateMap(int mineCount, int width, int height) {
    return CreateMap(mineCount, DEFAULT_RANDOM_WINDOW, width, height);
}

std::shared_ptr<IMap> IMapFactory::CreateMap(int mineCount, int randWindow, int width, int height) {
    /// ========== START ASSERTIONS =========== ///
    // Randomize assertions
    if (randWindow > RANDOM_MAX || randWindow < 0) {
        std::string str("[IMapFactory::CreateMap] Invalid random window: ");
        str.append(std::to_string(randWindow));
        throw std::runtime_error(str);
    }
    // Size assertion
    if (width < 0 || height < 0) {
        std::string str("[IMapFactory::CreateMap] Invalid map size: ");
        str.append(std::to_string(width));
        str.append(" x ");
        str.append(std::to_string(height));
        throw std::runtime_error(str);
    }
    /// ========== END ASSERTIONS =========== ///

    auto instance = std::make_shared<Map>(width, height);
    /// ========== Initialize C++11 randomizer =========== ///
    auto minesCoord = generateMines(mineCount, width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Coordinate coord(x, y);
            bool isMine = hasMine(*minesCoord, coord);
			instance->insertCell(coord, Cell(isMine));
        }
    }

    return instance;
}

static inline bool hasMine(std::vector<Coordinate>& vec, Coordinate coord) {
    for (auto& item : vec) {
        if (item.x == coord.x && item.y == coord.y) {
            return true;
        }
    }
    return false;
}

static std::unique_ptr<std::vector<Coordinate>> generateMines(int count, int width, int height) {
    auto res = std::make_unique<std::vector<Coordinate>>();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> wDist(0, width);
    std::uniform_int_distribution<int> hDist(0, height);

    int added = 0;
    while (added < count) {
         Coordinate c(wDist(mt), hDist(mt));
         if (!hasMine(*res, c)) {
             res->push_back(c);
             added++;
         }
    }

    return res;
}
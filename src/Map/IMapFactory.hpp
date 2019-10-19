//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "IMap.hpp"

static const int RANDOM_MAX = 0x7fffffff;

static const int DEFAULT_WIDTH = 10;
static const int DEFAULT_HEIGHT = 10;

static const int DEFAULT_RANDOM_WINDOW = static_cast<int>(static_cast<float>(RANDOM_MAX) * 0.95);

class IMapFactory {
public:
    IMapFactory() = delete;
    IMapFactory(const IMapFactory&) = delete;
    static IMap* CreateMap(int mineCount);
    static IMap* CreateMap(int mineCount, int randWindow);
    static IMap* CreateMap(int mineCount, int width, int height);
    static IMap* CreateMap(int mineCount, int randWindow, int width, int height);
};



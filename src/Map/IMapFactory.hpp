//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "IMap.hpp"
#include <memory>

static const int DEFAULT_WIDTH = 10;
static const int DEFAULT_HEIGHT = 10;

class IMapFactory {
public:
    IMapFactory() = delete;
    IMapFactory(const IMapFactory&) = delete;
    static std::shared_ptr<IMap> CreateMap(int mineCount);
    static std::shared_ptr<IMap> CreateMap(int mineCount, int width, int height);
};

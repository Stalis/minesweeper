//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "../Map/Coordinate.hpp"
#include <functional>

enum class CellMode {
    CLOSED,
    EMPTY,
    MINE,
};

class IGameView {
public:
    using TOpenCallback = std::function<void (Vector2)>;
public:
    virtual ~IGameView() = default;

    virtual void draw() = 0;
    virtual void setOpenCallback(TOpenCallback* callback) = 0;
};

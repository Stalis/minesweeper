//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "src/Vector2.hpp"
#include "src/Command.hpp"
#include <functional>

enum class CellMode {
    CLOSED,
    EMPTY,
    MINE,
};

class IGameView {
public:
    using TCommandCallback = std::function<void (Command)>;
public:
    virtual ~IGameView() = default;

    virtual void draw() = 0;
    virtual void setCommandCallback(TCommandCallback* callback) = 0;
	virtual Command waitInput() = 0;
};

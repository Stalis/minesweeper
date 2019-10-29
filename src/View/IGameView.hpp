//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "src/Command.hpp"
#include "src/Controller/IController.hpp"
#include "src/Vector2.hpp"
#include <functional>

class IGameView {
public:
    using TCommandCallback = std::function<void(Command)>;

public:
    virtual ~IGameView() = default;

    virtual void draw() = 0;
    virtual void setCommandCallback(TCommandCallback* callback) = 0;
    virtual Command waitInput() = 0;
    virtual const IController& getController() const = 0;
};

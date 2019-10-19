//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include <map>
#include "CellInfo.hpp"
#include "../Vector2.hpp"
#include "../Command.hpp"

class IGameViewModel {
public:
    using TCellRow = std::vector<CellInfo>;
    using TCellMatrix = std::vector<TCellRow>;
public:
    virtual ~IGameViewModel() = default;

    virtual void executeCommand(Command cmd) = 0;
    virtual TCellMatrix& getCellGrid() = 0;
    virtual void movePointer(const Vector2& pos) = 0;
};

//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include <map>
#include <vector>
#include "CellInfo.hpp"
#include "src/Vector2.hpp"
#include "src/Command.hpp"
#include "src/GameState.hpp"

class IGameViewModel {
public:
    using TCellRow = std::vector<CellInfo>;
    using TCellMatrix = std::vector<TCellRow>;
public:
    virtual ~IGameViewModel() = default;

    virtual void executeCommand(Command cmd) = 0;
    virtual TCellMatrix& getCellGrid() = 0;
    virtual void processGameState(GameState state) = 0;
    virtual GameState getGameState() = 0;
};

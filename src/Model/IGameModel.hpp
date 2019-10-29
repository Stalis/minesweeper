//
// Created by Stanislav on 28/10/2019.
//

#pragma once

#include "CellInfo.hpp"
#include "src/Command.hpp"
#include "src/GameState.hpp"

#include <vector>

class IGameModel {
public:
    using TCellRow = std::vector<CellInfo>;
    using TCellMatrix = std::vector<TCellRow>;

    virtual void executeCommand(Command cmd) = 0;
    virtual const TCellMatrix& getCellGrid() const = 0;
    virtual GameState getGameState() const = 0;
    virtual bool checkIsWin() const = 0;
};

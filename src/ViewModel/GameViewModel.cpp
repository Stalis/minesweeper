//
// Created by Stanislav on 19/10/2019.
//

#include "GameViewModel.hpp"

void GameViewModel::executeCommand(Command cmd) {
}

IGameViewModel::TCellMatrix& GameViewModel::getCellGrid() {
    int width = _map->getWidth();
    int height = _map->getHeight();

    auto* res = new TCellMatrix();
    res->reserve(height);

    for (int y = 0; y < height; y++) {
        TCellRow row{width};
        for (int x = 0; x < width; x++) {
            row.push_back(getCellInfo(Coordinate{x, y}));
        }
        res->push_back(row);
    }

    auto* buf = _array;
    _array = res;
    delete buf;
    return *_array;
}

CellInfo GameViewModel::getCellInfo(const Coordinate& coord) const {
    if (_map->isMine(coord)) {
        return CellInfo(true);
    }

    auto neighbours = _map->getNeighbours(coord);
    int count = 0;
    for (auto& item : neighbours) {
        if (_map->isMine(item)) {
            count++;
        }
    }

    return CellInfo(count);
}

void GameViewModel::movePointer(const Vector2& pos) {
}

void GameViewModel::processGameState(GameState state) {
}

//
// Created by Stanislav on 19/10/2019.
//

#include "GameViewModel.hpp"

void GameViewModel::executeCommand(Command cmd) {
    if (_state == GameState::LOSE || _state == GameState::WIN) {
        _state = GameState::EXIT;
        return;
    }
	if (cmd.type == CommandType::OPEN)
	{
		openCell(cmd.x, cmd.y);
	}
}

IGameViewModel::TCellMatrix& GameViewModel::getCellGrid() {
    if (nullptr == _array) {
        initCellGrid();
    }
    return *_array;
}

CellInfo GameViewModel::getCellInfo(const Coordinate& coord) const {
    auto neighbours = _map->getNeighbours(coord);
    int count = 0;
    for (auto& item : neighbours) {
        if (_map->isMine(item)) {
            count++;
        }
    }

    if (_map->isMine(coord)) {
        return CellInfo{true, count};
    }

    return CellInfo{count};
}

void GameViewModel::initCellGrid() {
    int width = _map->getWidth();
    int height = _map->getHeight();

    auto res = std::make_unique<TCellMatrix>();

    for (int y = 0; y < height; y++) {
        TCellRow row{};
        for (int x = 0; x < width; x++) {
            row.push_back(getCellInfo(Coordinate{x, y}));
        }
        res->push_back(row);
    }
    _array = std::move(res);
}

void GameViewModel::openCell(int x, int y)
{
    if (x < 0 || y < 0)
        return;

    if (y < _array->size() && x < _array->at(y).size()) {
        auto& info = _array->at(y).at(x);
        bool isMine = false;
        info.open(isMine);
        if (isMine) {
            processGameState(GameState::LOSE);
        }
    }
}

void GameViewModel::processGameState(GameState state) {
	_state = state;

	if (state == GameState::LOSE || state == GameState::WIN)
	{
        bool _ = false;
        for (auto& row : *_array) {
            for (auto& x : row)
			{
                x.open(_);
			}
		}
	}
}

GameState GameViewModel::getGameState() {
    return _state;
}
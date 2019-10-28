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
	if (cmd.type == CommandType::MARK)
	{
		markCell(cmd.x, cmd.y);
	}
	if (cmd.type == CommandType::UNMARK)
	{
		unmarkCell(cmd.x, cmd.y);
	}
}

IGameViewModel::TCellMatrix& GameViewModel::getCellGrid() {
    if (nullptr == _array) {
        initCellGrid();
    }
    return *_array;
}

[[nodiscard]]
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
		if (!info.isMarked())
		{
			info.open(isMine);
		}
        if (isMine) {
            processGameState(GameState::LOSE);
        } else {
            processGameState(GameState::GAME);
        }
    }
}

void GameViewModel::markCell(int x, int y)
{
	if (x < 0 || y < 0)
		return;

	if (y < _array->size() && x < _array->at(y).size())
	{
		auto& info = _array->at(y).at(x);
		info.mark();
	}
}

void GameViewModel::unmarkCell(int x, int y)
{
	if (x < 0 || y < 0)
		return;

	if (y < _array->size() && x < _array->at(y).size())
	{
		auto& info = _array->at(y).at(x);
		info.unmark();
	}
}

void GameViewModel::processGameState(GameState state) {
	_state = state;
    if (checkIsWin()) {
        _state = GameState::WIN;
    }

	if (_state == GameState::LOSE || _state == GameState::WIN)
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

bool GameViewModel::checkIsWin() const {
    bool isMine = false;
    bool allClosedIsMines = true;

    // if on cell contains no mine - `allClosedIsMines` turns to false
    for (auto& row : *_array) {
        for (auto& cell : row) {
            if (!cell.isOpened(isMine)) {
                allClosedIsMines &= isMine;
            }
        }
    }

    return allClosedIsMines;
}

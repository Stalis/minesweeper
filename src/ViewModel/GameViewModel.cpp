//
// Created by Stanislav on 19/10/2019.
//

#include "GameViewModel.hpp"

void GameViewModel::executeCommand(Command cmd) {
	if (cmd.type == CommandType::OPEN)
	{
		openCell(cmd.x, cmd.y);
	}
}

IGameViewModel::TCellMatrix& GameViewModel::getCellGrid() {
	if (nullptr != _array)
	{
		return *_array;
	}

    int width = _map->getWidth();
    int height = _map->getHeight();

    auto* res = new TCellMatrix();
    //res->reserve(height);

    for (int y = 0; y < height; y++) {
        TCellRow row{};
        for (int x = 0; x < width; x++) {
            row.push_back(getCellInfo(Coordinate{x, y}));
        }
        res->push_back(row);
    }
	_array->resize(res->size());
	std::copy(res->begin(), res->end(), _array->begin());
	delete res;
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

void GameViewModel::openCell(int x, int y)
{
	auto& info = _array->at(y).at(x);
	bool isMine = false;
	info.open(isMine);
	if (isMine)
	{

	}
}

void GameViewModel::movePointer(const Vector2& pos) {
}

void GameViewModel::processGameState(GameState state) {
}

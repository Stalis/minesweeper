//
// Created by Stanislav on 28/10/2019.
//

#include "GameModel.hpp"
#include <memory>

static inline CellInfo getCellInfo(const IMap& map, const Coordinate& coord);

GameModel::GameModel(const IMap& map)
    : _state(GameState::GAME), _map(loadMap(map)) {}

void GameModel::executeCommand(Command cmd) {
    if (isEndGame()) {
        exitGame();
    }

    switch (cmd.type) {
    case CommandType::OPEN:openCell(cmd.x, cmd.y);
        break;
    case CommandType::MARK:markCell(cmd.x, cmd.y);
        break;
    case CommandType::UNMARK:unmarkCell(cmd.x, cmd.y);
        break;
    case CommandType::EXIT:exitGame();
        break;
    default:break;
    }
}

const IGameModel::TCellMatrix& GameModel::getCellGrid() const {
    return *_map;
}

GameState GameModel::getGameState() const {
    return _state;
}

bool GameModel::checkIsWin() const {
    return false;
}

std::unique_ptr<IGameModel::TCellMatrix> GameModel::loadMap(const IMap& map) const {
    int width = map.getWidth();
    int height = map.getHeight();

    auto res = std::make_unique<TCellMatrix>();

    for (int y = 0; y < height; y++) {
        TCellRow row{};
        for (int x = 0; x < width; x++) {
            row.push_back(getCellInfo(map, Coordinate{x, y}));
        }
        res->push_back(row);
    }
    return res;
}

void GameModel::openCell(int x, int y) {
    if (x < 0 || y < 0)
        return;

    if (y < _map->size() && x < _map->at(y).size()) {
        auto& info = _map->at(y).at(x);
        bool isMine = false;
        if (!info.isMarked()) {
            info.open(isMine);
        }
        if (isMine) {
            setGameState(GameState::LOSE);
        } else {
            setGameState(GameState::GAME);
        }
    }
}

void GameModel::markCell(int x, int y) {
    if (x < 0 || y < 0)
        return;

    if (y < _map->size() && x < _map->at(y).size()) {
        auto& info = _map->at(y).at(x);
        info.mark();
    }
}

void GameModel::unmarkCell(int x, int y) {
    if (x < 0 || y < 0)
        return;

    if (y < _map->size() && x < _map->at(y).size()) {
        auto& info = _map->at(y).at(x);
        info.unmark();
    }
}

void GameModel::exitGame() {
    _state = GameState::EXIT;
}

bool GameModel::isEndGame() const {
    return _state == GameState::WIN || _state == GameState::LOSE;
}

void GameModel::setGameState(GameState state) {
    _state = state;
}

static inline CellInfo getCellInfo(const IMap& map, const Coordinate& coord) {
    auto neighbours = map.getNeighbours(coord);
    int count = 0;
    for (auto& item : neighbours) {
        if (map.isMine(item)) {
            count++;
        }
    }

    if (map.isMine(coord)) {
        return CellInfo{true, count};
    }

    return CellInfo{count};
}



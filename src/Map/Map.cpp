//
// Created by Stanislav on 19/10/2019.
//

#include "Map.hpp"

Map::Map(int width, int height)
    : _cells(std::map<Coordinate, Cell>{})
    , _width(width)
    , _height(height) {
}

bool Map::isMine(const Coordinate& cell) const {
    auto* c = getCell(cell);
    if (nullptr != c)
        return c->hasMine();
    return false;
}

std::vector<Coordinate> Map::getNeighbours(const Coordinate& coord) const {
    std::vector<Coordinate> res;

    auto appendIfExist = [this, &res](int x, int y) -> void {
        Coordinate c(x, y);
        if (nullptr != getCell(c)) {
            res.push_back(c);
        }
    };

    if (getCell(coord) != nullptr) {
        appendIfExist(coord.x - 1, coord.y - 1);
        appendIfExist(coord.x, coord.y - 1);
        appendIfExist(coord.x + 1, coord.y - 1);

        appendIfExist(coord.x - 1, coord.y);
        appendIfExist(coord.x + 1, coord.y);

        appendIfExist(coord.x - 1, coord.y + 1);
        appendIfExist(coord.x, coord.y + 1);
        appendIfExist(coord.x + 1, coord.y + 1);
    }

    return res;
}

void Map::insertCell(const Coordinate& coord, const Cell& cell) {
    _cells.insert_or_assign(coord, cell);
}

const Cell* Map::getCell(const Coordinate& coord) const {
    auto iter = _cells.find(coord);
    if (iter == _cells.end())
        return nullptr;
    return &iter->second;
}

int Map::getWidth() const {
    return _width;
}

int Map::getHeight() const {
    return _height;
}

//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include <map>
#include "Cell.hpp"
#include "Coordinate.hpp"
#include "IMap.hpp"

class Map : public IMap {
public:
    Map(int width, int height);
    virtual ~Map() = default;
    bool isMine(const Coordinate&) const override;
    std::vector<Coordinate> getNeighbours(const Coordinate& coord) const override;
    int getWidth() const override;
    int getHeight() const override;
    std::map<Coordinate, Cell> _cells;

private:
    const Cell* getCell(const Coordinate&) const;
    int _width, _height;
};



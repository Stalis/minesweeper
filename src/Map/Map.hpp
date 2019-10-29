//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "Cell.hpp"
#include "Coordinate.hpp"
#include "IMap.hpp"
#include <map>

class Map : public IMap {
public:
    Map(int width, int height);
    virtual ~Map() = default;
    bool isMine(const Coordinate&) const override;
    std::vector<Coordinate> getNeighbours(const Coordinate& coord) const override;
    int getWidth() const override;
    int getHeight() const override;
    void insertCell(const Coordinate&, const Cell&);

private:
    const Cell* getCell(const Coordinate&) const;
    std::map<Coordinate, Cell> _cells;
    int _width, _height;
};

//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "Coordinate.hpp"
#include <vector>

class IMap {
public:
    virtual ~IMap() = default;

    virtual bool isMine(const Coordinate&) const = 0;
    virtual std::vector<Coordinate> getNeighbours(const Coordinate& coord) const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};

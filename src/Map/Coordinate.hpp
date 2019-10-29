//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "src/Vector2.hpp"

class Coordinate : public Vector2 {
public:
    Coordinate(const Coordinate&) = default;
    Coordinate(int x, int y)
        : Vector2(x, y) {
    }
    /// For sorting in std::map
    bool operator<(const Coordinate& other) const {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
};

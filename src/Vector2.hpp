//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include <cmath>

class Vector2 {
public:
    const int x, y;

    Vector2() : Vector2(0, 0) {}
	Vector2(const Vector2&) = default;
    Vector2(int x, int y) : x(x), y(y) {}

    float length() const {
        return sqrt(static_cast<float>(x * x) + static_cast<float>(y * y));
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2{x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2{x - other.x, y - other.y};
    }

    Vector2 operator*(int coefficient) {
        return Vector2{x * coefficient, y * coefficient};
    }

    Vector2 operator/(int coefficient) {
        return Vector2{x / coefficient, y / coefficient};
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
};

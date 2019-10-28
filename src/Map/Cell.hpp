//
// Created by Stanislav on 19/10/2019.
//

#pragma once

class Cell {
public:
	Cell(bool isMine) : _hasMine(isMine) {};
	Cell(const Cell&) = default;
    bool hasMine() const { return _hasMine; }

    Cell& operator=(const Cell& other) = default;
private:
    bool _hasMine = false;
};



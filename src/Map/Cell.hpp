//
// Created by Stanislav on 19/10/2019.
//

#pragma once

class Cell {
public:
    Cell(bool isMine) : _hasMine(isMine) {}
    bool hasMine() const { return _hasMine; }
private:
    const bool _hasMine = false;
};



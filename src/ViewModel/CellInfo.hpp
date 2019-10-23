//
// Created by Stanislav on 19/10/2019.
//

#pragma once

class CellInfo {
public:
    CellInfo(bool mine, int nearMines) :
        _nearMines(nearMines), _isMine(mine) {}

    explicit CellInfo(int nearMines) : _nearMines(nearMines) {}

    bool isOpened() const { return _opened; }

    bool isOpened(bool& isMine) const {
        isMine = _isMine;
        return _opened;
    }

    int nearMines() const { return _nearMines; }

    void open(bool& isMine) {
        _opened = true;
        isMine = _isMine;
    }

private:
    int _nearMines = 0;
    bool _opened = false;
    bool _isMine = false;
};

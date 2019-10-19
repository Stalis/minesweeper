//
// Created by Stanislav on 19/10/2019.
//

#include "ConsoleGameView.hpp"
#include <iostream>
#include <vector>

static const char ClosedCell = '#';
static const char MineCell = '*';
static const char EmptyCell = ' ';
static const char Delimiter = ' ';
static char getCellChar(const CellInfo& info);

ConsoleGameView::ConsoleGameView(IGameViewModel* viewModel)
    : _gridView(std::map<Coordinate, char>{}), _viewModel(viewModel) {

//    input_on();
}

void ConsoleGameView::draw() {
    std::system("clear");

    auto& grid = _viewModel->getCellGrid();
    for (auto& row : grid) {
        std::cout << Delimiter << std::flush;
        for (auto& item : row) {
            std::cout << getCellChar(item) << Delimiter << std::flush;
        }
        std::cout << std::endl;
    }
}

void ConsoleGameView::setOpenCallback(IGameView::TOpenCallback* callback) {
}

static char getCellChar(const CellInfo& info) {
    bool isMine = false;
    if (info.isOpened(isMine)) {
        if (!isMine) {
            int near = info.nearMines();
            if (0 == near) {
                return EmptyCell;
            }
            return std::to_string(near)[0];
        }
        return MineCell;
    }
    return ClosedCell;
}


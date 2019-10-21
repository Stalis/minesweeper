//
// Created by Stanislav on 19/10/2019.
//

#include "ConsoleGameView.hpp"
#include <iostream>
#include <vector>
#include <string>

#include "../Utils.hpp"

static const char ClosedCell = '#';
static const char MineCell = '*';
static const char EmptyCell = ' ';
static const char Delimiter = ' ';
static char getCellChar(const CellInfo& info);

ConsoleGameView::ConsoleGameView(IGameViewModel* viewModel)
    : _gridView(std::map<Coordinate, char>{}), _viewModel(viewModel) {
}

void ConsoleGameView::draw() {
	Utils::clear_screen();

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
            int nearMines = info.nearMines();
            if (0 == nearMines) {
                return EmptyCell;
            }
            return std::to_string(nearMines)[0];
        }
        return MineCell;
    }
    return ClosedCell;
}


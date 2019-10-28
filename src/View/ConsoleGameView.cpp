//
// Created by Stanislav on 19/10/2019.
//

#include "ConsoleGameView.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "src/Utils.hpp"

static void printHeader(int count, char delimiter);

static bool readColumnNumber(const std::string& name, int& number);
static bool readColumnName(int number, std::string& name);

static const ConsoleCommandReader::TConverter tConverterRef{readColumnNumber};
inline static const ConsoleGameViewSettings defaultSettings = ConsoleGameViewSettings{};

static const std::string HeaderAlphabet{"abcdefghjklmnopqrstuvwxyz"};

ConsoleGameView::ConsoleGameView(std::shared_ptr<IGameViewModel> viewModel)
    : ConsoleGameView(viewModel, defaultSettings) {}

ConsoleGameView::ConsoleGameView(std::shared_ptr<IGameViewModel> viewModel, const ConsoleGameViewSettings& settings)
    : _settings(settings), _gridView(std::map<Coordinate, char>{}), _viewModel(std::move(viewModel)),
      _commandCallback(nullptr),
      _commandReader(std::make_unique<ConsoleCommandReader>(tConverterRef)) {}

void ConsoleGameView::draw()
{
	Utils::clear_screen();

    switch (_viewModel->getGameState()) {
    case GameState::GAME:
		drawGameScreen();
        break;
    case GameState::WIN:
		drawWinScreen();
        break;
    case GameState::LOSE:
		drawLoseScreen();
        break;
    case GameState::EXIT:
		std::cout << "Exiting..." << std::endl;
        break;
    }
}

void ConsoleGameView::setCommandCallback(IGameView::TCommandCallback* callback) {
    if (nullptr != callback) {
        _commandCallback = callback;
    }
}

Command ConsoleGameView::waitInput()
{
	std::string input{};
	std::getline(std::cin, input);
    auto cmd = _commandReader->convertToCommand(input);
//    std::cin.get();
    if (nullptr != _commandCallback) {
        (*_commandCallback)(cmd);
    }
    return cmd;
}

void ConsoleGameView::toLoseScreen() {
}

void ConsoleGameView::toWinScreen() {
}

void ConsoleGameView::drawWinScreen() {
	drawMap();
    std::cout << ConsoleColors::BrightGreen << "Yow win!" << ConsoleColors::Reset << std::endl;
}

void ConsoleGameView::drawLoseScreen() {
	drawMap();
    std::cout << ConsoleColors::Red << "You lose!" << ConsoleColors::Reset << std::endl;
}

void ConsoleGameView::drawGameScreen() {
	drawMap();

    std::cout << "> " << std::flush;
}

void ConsoleGameView::drawMap()
{
	auto& grid = _viewModel->getCellGrid();
	std::cout << _settings.delimiter << _settings.delimiter << _settings.headerColor << std::flush;
	printHeader(grid.size(), _settings.delimiter);
	std::cout << _settings.resetColor << std::endl;

	int counter = 1;
	for (auto& row : grid)
	{
		std::cout << _settings.rowNumberColor << counter++ << _settings.resetColor << _settings.delimiter << std::flush;
		for (auto& item : row)
		{
			putCellChar(item);
			std::cout << _settings.delimiter << std::flush;
		}
		std::cout << _settings.resetColor << std::endl;
	}
}

void ConsoleGameView::putCellChar(const CellInfo& info) {
    std::string colorSwitch;
    std::string resetSwitch = _settings.resetColor;
    char ch;

	bool isMine = false;
	if (info.isOpened(isMine))
	{
		if (!isMine)
		{
			int nearMines = info.nearMines();
			if (0 == nearMines)
			{
                colorSwitch = _settings.emptyColor;
                ch = _settings.emptyCell;
            } else {
                colorSwitch = _settings.neighbourColor;
                ch = std::to_string(nearMines)[0];
			}
        } else {
            colorSwitch = _settings.mineColor;
            ch = _settings.mineCell;
        }
    } else {
        colorSwitch = _settings.closedColor;
        ch = _settings.closedCell;
    }

    std::cout << colorSwitch << ch << resetSwitch << std::flush;
}

static void printHeader(int count, char delimiter) {
    std::string columnName{};
	for (int i = 0; i < count; i++)
	{
        if (readColumnName(i, columnName)) {
            std::cout << columnName << delimiter << std::flush;
        }
	}
}

static bool readColumnNumber(const std::string& name, int& number) {
    number = static_cast<int>(HeaderAlphabet.find_first_of(name.front(), 0));
    return number != std::string::npos;
}

static bool readColumnName(int number, std::string& name) {
    if (number < 0 || number > (HeaderAlphabet.length() - 1)) {
        return false;
    }
    name = HeaderAlphabet.at(number);
    return true;
}

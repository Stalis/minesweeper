//
// Created by Stanislav on 19/10/2019.
//

#include "ConsoleGameView.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "src/Utils.hpp"

static Command parseInput(const std::string& input);
static void printHeader(int count, char delimiter);
static int getColumnNumber(const std::string& name);
static std::string getColumnName(int number);

inline static const ConsoleGameViewSettings defaultSettings{
    .mineCell = '*',
    .closedCell = '#',
    .emptyCell = '.',
    .delimiter = ' ',
    .headerColor = ConsoleColors::BrightYellow,
    .rowNumberColor = defaultSettings.headerColor,
    .mineColor = ConsoleColors::Red,
    .closedColor = ConsoleColors::BrightWhite,
    .neighbourColor = ConsoleColors::Yellow,
    .emptyColor = ConsoleColors::Reset,
    .resetColor = ConsoleColors::Reset,
};

ConsoleGameView::ConsoleGameView(IGameViewModel* viewModel)
    : ConsoleGameView(viewModel, defaultSettings) {}

ConsoleGameView::ConsoleGameView(IGameViewModel* viewModel, const ConsoleGameViewSettings& settings)
    : _settings(settings), _gridView(std::map<Coordinate, char>{}), _viewModel(viewModel),
      _commandCallback(nullptr) {}

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
    auto cmd = parseInput(input);
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
    std::cout << ConsoleColors::BrightGreen << "Yow win!" << ConsoleColors::Reset << std::endl;
}

void ConsoleGameView::drawLoseScreen() {
    std::cout << ConsoleColors::Red << "You lose!" << ConsoleColors::Reset << std::endl;
}

void ConsoleGameView::drawGameScreen() {
    auto& grid = _viewModel->getCellGrid();
    std::cout << _settings.delimiter << _settings.delimiter << _settings.headerColor << std::flush;
    printHeader(grid.size(), _settings.delimiter);
    std::cout << _settings.resetColor << std::endl;

    int counter = 1;
    for (auto& row : grid) {
        std::cout << _settings.rowNumberColor << counter++ << _settings.resetColor << _settings.delimiter << std::flush;
        for (auto& item : row) {
            putCellChar(item);
            std::cout << _settings.delimiter << std::flush;
        }
        std::cout << _settings.resetColor << std::endl;
    }

    std::cout << "> " << std::flush;
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

static Command parseInput(const std::string& input)
{
    if (input.length() == 0) {
        return Command::INVALID;
    }
	std::vector<std::string> words{};
    std::stringstream stream(input);
    {
        std::string word;
        while (std::getline(stream, word, ' ')) {
            words.push_back(word);
        }
    }

	for (auto& word : words)
	{
		std::cout << word << std::endl;
	}

	if (words.at(0) == "exit")
	{
		return Command::EXIT;
	}

	if (words.at(0) == "open")
	{
		int x = getColumnNumber(words.at(1));
		int y = std::stoi(words.at(2)) - 1;
		return Command::Open(x, y);
	}

    if (words.at(0).length() == 1) {
        int x = getColumnNumber(words.at(0));
        int y = std::stoi(words.at(1)) - 1;
        return Command::Open(x, y);
    }

    std::cin.get();
	return Command::INVALID;
}

void printHeader(int count, char delimiter)
{
	for (int i = 0; i < count; i++)
	{
        std::cout << getColumnName(i) << delimiter << std::flush;
	}
}

static int getColumnNumber(const std::string& name)
{
	return name.at(0) - 'a';
}

static std::string getColumnName(int number)
{
	char res = 'a' + number;
	return std::string{ res };
}

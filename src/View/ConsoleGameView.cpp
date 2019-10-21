//
// Created by Stanislav on 19/10/2019.
//

#include "ConsoleGameView.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "src/Utils.hpp"

static const char ClosedCell = '#';
static const char MineCell = '*';
static const char EmptyCell = ' ';
static const char Delimiter = ' ';

static char getCellChar(const CellInfo& info);
static Command parseInput(const std::string& input);
static void printHeader(int count);
static int getColumnNumber(const std::string& name);
static std::string getColumnName(int number);

ConsoleGameView::ConsoleGameView(IGameViewModel* viewModel)
	: _gridView(std::map<Coordinate, char>{}), _viewModel(viewModel)
{}

void ConsoleGameView::draw()
{
	Utils::clear_screen();

	auto& grid = _viewModel->getCellGrid();
	std::cout << Delimiter << Delimiter << std::flush;
	printHeader(grid.size());
	std::cout << std::endl;

	int counter = 1;
	for (auto& row : grid)
	{
		std::cout << counter++ << Delimiter << std::flush;

		for (auto& item : row)
		{
			std::cout << getCellChar(item) << Delimiter << std::flush;
		}
		std::cout << std::endl;
	}

	std::cout << "> " << std::flush;
}

void ConsoleGameView::setCommandCallback(IGameView::TCommandCallback* callback)
{}

Command ConsoleGameView::waitInput()
{
	std::string input{};
	std::getline(std::cin, input);

	return parseInput(input);
}

static char getCellChar(const CellInfo& info)
{
	bool isMine = false;
	if (info.isOpened(isMine))
	{
		if (!isMine)
		{
			int nearMines = info.nearMines();
			if (0 == nearMines)
			{
				return EmptyCell;
			}
			return std::to_string(nearMines) [0];
		}
		return MineCell;
	}
	return ClosedCell;
}

static Command parseInput(const std::string& input)
{
	std::vector<std::string> words{};
    std::stringstream stream(input);
    std::string word;
    while (std::getline(stream, word, ' ')) {
        words.push_back(word);
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

    std::cin.get();
	return Command::INVALID;
}

void printHeader(int count)
{
	for (int i = 0; i < count; i++)
	{
		std::cout << getColumnName(i) << Delimiter << std::flush;
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

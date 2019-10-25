//
// Created by Stanislav on 19/10/2019.
//

#pragma once
#include <map>
#include <string>
#include <functional>
#include "IGameView.hpp"
#include "src/Map/Coordinate.hpp"
#include "src/ViewModel/IGameViewModel.hpp"
#include "ConsoleColors.hpp"

struct ConsoleGameViewSettings {
    const char mineCell = '*';
    const char closedCell = '#';
    const char emptyCell = '.';
    const char delimiter = ' ';
    const std::string& headerColor = ConsoleColors::BrightYellow;
    const std::string& rowNumberColor = headerColor;
    const std::string& mineColor = ConsoleColors::Red;
    const std::string& closedColor = ConsoleColors::BrightWhite;
    const std::string& neighbourColor = ConsoleColors::Yellow;
    const std::string& emptyColor = ConsoleColors::Reset;
    const std::string& resetColor = ConsoleColors::Reset;
};

class ConsoleGameView : public IGameView {
public:
    explicit ConsoleGameView(std::shared_ptr<IGameViewModel> viewModel);
    ConsoleGameView(std::shared_ptr<IGameViewModel> viewModel, const ConsoleGameViewSettings& settings);
    ~ConsoleGameView() override = default;

    void draw() override;
    void setCommandCallback(TCommandCallback* callback) override;
    Command waitInput() override;
    void toWinScreen() override;
    void toLoseScreen() override;
private:
    ConsoleGameViewSettings _settings;
    std::map<Coordinate, char> _gridView;
    std::shared_ptr<IGameViewModel> _viewModel;
    TCommandCallback* _commandCallback;

    void drawWinScreen();
    void drawLoseScreen();
    void drawGameScreen();
	void drawMap();
    void putCellChar(const CellInfo& info);
};



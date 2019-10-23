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
    const char mineCell;
    const char closedCell;
    const char emptyCell;
    const char delimiter;
    const std::string& headerColor;
    const std::string& rowNumberColor;
    const std::string& mineColor;
    const std::string& closedColor;
    const std::string& neighbourColor;
    const std::string& emptyColor;
    const std::string& resetColor;
};

class ConsoleGameView : public IGameView {
public:
    explicit ConsoleGameView(IGameViewModel* viewModel);
    ConsoleGameView(IGameViewModel* viewModel, const ConsoleGameViewSettings& settings);
    ~ConsoleGameView() override = default;

    void draw() override;
    void setCommandCallback(TCommandCallback* callback) override;
    Command waitInput() override;
    void toWinScreen() override;
    void toLoseScreen() override;
private:
    ConsoleGameViewSettings _settings;
    std::map<Coordinate, char> _gridView;
    IGameViewModel* _viewModel;
    TCommandCallback* _commandCallback;

    void drawWinScreen();
    void drawLoseScreen();
    void drawGameScreen();
    void putCellChar(const CellInfo& info);
};



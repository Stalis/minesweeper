//
// Created by Stanislav on 19/10/2019.
//

#pragma once
#include <map>
#include <string>
#include <functional>
#include <src/Controller/TextCommandController.hpp>
#include <src/Model/IGameModel.hpp>
#include "IGameView.hpp"
#include "src/Map/Coordinate.hpp"
#include "ConsoleColors.hpp"

struct ConsoleGameViewSettings {
    const char mineCell = '*';
    const char closedCell = '#';
    const char emptyCell = '.';
	const char markedCell = 'O';
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
    explicit ConsoleGameView(std::shared_ptr<IGameModel> model);
    ConsoleGameView(std::shared_ptr<IGameModel>, const ConsoleGameViewSettings&);
    ConsoleGameView(std::shared_ptr<IGameModel>, std::unique_ptr<TextCommandController>);
    ConsoleGameView(std::shared_ptr<IGameModel>,
                    std::unique_ptr<TextCommandController>,
                    const ConsoleGameViewSettings&);
    ~ConsoleGameView() override = default;

    void draw() override;
    void setCommandCallback(TCommandCallback* callback) override;
    const IController& getController() const override;
    Command waitInput() override;
private:
    ConsoleGameViewSettings _settings;
    std::map<Coordinate, char> _gridView;
    std::shared_ptr<IGameModel> _model;
    TCommandCallback* _commandCallback;
    std::unique_ptr<TextCommandController> _controller;

    void drawWinScreen();
    void drawLoseScreen();
    void drawGameScreen();
	void drawMap();
    void putCellChar(const CellInfo& info);
};



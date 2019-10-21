//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "View/IGameView.hpp"
#include "Map/Map.hpp"
#include "ViewModel/IGameViewModel.hpp"

struct GameSettings {
    int width = 8;
    int height = 8;
    int mines = 10;
};

class Game {
public:
    Game();
    explicit Game(const GameSettings&);
    void update();
    bool isExitState() const;
    ~Game();
private:
    IGameView* _view;
    IGameViewModel* _viewModel;
    IMap* _map;
    GameSettings _settings;
    GameState _state;
    void processInput() const;
    void draw() const;
};



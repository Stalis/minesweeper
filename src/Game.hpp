//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "View/IGameView.hpp"
#include "Map/Map.hpp"
#include "ViewModel/IGameViewModel.hpp"
#include <memory>

struct GameSettings {
    int width = 8;
    int height = 8;
    int mines = 10;
};

class Game {
public:
    Game();
    explicit Game(const GameSettings&);
	void init();
    void update();
    bool isExitState() const;
    ~Game();
private:
    std::shared_ptr<IGameView> _view;
    std::shared_ptr<IGameViewModel> _viewModel;
    std::shared_ptr<IMap> _map;
    GameSettings _settings;
    mutable GameState _state;
    void processInput() const;
    void draw() const;
};



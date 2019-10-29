//
// Created by Stanislav on 19/10/2019.
//

#include "Game.hpp"
#include "Map/IMapFactory.hpp"
#include "View/ConsoleGameView.hpp"
#include <chrono>
#include <thread>
#include <memory>
#include <src/Model/GameModel.hpp>

Game::Game()
    : Game(GameSettings{}) {}

Game::Game(const GameSettings& settings)
    : _settings(settings), _state(GameState::GAME) {
    _map = IMapFactory::CreateMap(_settings.mines, _settings.width, _settings.height);
    _model = std::make_shared<GameModel>(*_map);
    _view = std::make_shared<ConsoleGameView>(_model);
}

void Game::init() {
    draw();
}

void Game::update() {
    processInput();
    draw();
    _state = _model->getGameState();
}

bool Game::isExitState() const {
    return _state == GameState::EXIT;
}

void Game::processInput() const {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
    auto cmd = _view->waitInput();
    if (cmd.type == CommandType::EXIT) {
        _state = GameState::EXIT;
    }
    _model->executeCommand(cmd);
}

void Game::draw() const {
    _view->draw();
}

Game::~Game() {
    _view.~shared_ptr();
    _model.~shared_ptr();
    _map.~shared_ptr();
}

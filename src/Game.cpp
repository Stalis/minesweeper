//
// Created by Stanislav on 19/10/2019.
//

#include "Game.hpp"
#include "Map/IMapFactory.hpp"
#include "View/ConsoleGameView.hpp"
#include "ViewModel/GameViewModel.hpp"
#include <chrono>
#include <thread>

Game::Game()
    : Game(GameSettings{}){ }

Game::Game(const GameSettings& settings)
    : _settings(settings), _state(GameState::GAME) {
    _map = IMapFactory::CreateMap(_settings.mines, _settings.width, _settings.height);
    _viewModel = new GameViewModel(_map);
    _view = new ConsoleGameView(_viewModel);
}

void Game::init()
{
	draw();
}

void Game::update() {
    processInput();
    draw();
}

bool Game::isExitState() const {
    return _state == GameState::EXIT;
}

void Game::processInput() const {
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
	auto cmd = _view->waitInput();
	if (cmd.type == CommandType::EXIT)
	{
		_state = GameState::EXIT;
	}
	_viewModel->executeCommand(cmd);
}

void Game::draw() const {
    _view->draw();
}

Game::~Game() {
    delete _view;
    delete _viewModel;
    delete _map;
}

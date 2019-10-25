//
// Created by Stanislav on 19/10/2019.
//

#include "Game.hpp"
#include "Map/IMapFactory.hpp"
#include "View/ConsoleGameView.hpp"
#include "ViewModel/GameViewModel.hpp"
#include <chrono>
#include <thread>
#include <memory>

Game::Game()
    : Game(GameSettings{}){ }

Game::Game(const GameSettings& settings)
    : _settings(settings), _state(GameState::GAME) {
    _map = IMapFactory::CreateMap(_settings.mines, _settings.width, _settings.height);
    _viewModel = std::make_shared<GameViewModel>(_map);
    _view = std::make_shared<ConsoleGameView>(_viewModel);
}

void Game::init()
{
	draw();
}

void Game::update() {
    processInput();
    draw();
    _state = _viewModel->getGameState();
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
		_viewModel->processGameState(_state);
	} else
	{
		_viewModel->executeCommand(cmd);
	}
}

void Game::draw() const {
    _view->draw();
}

Game::~Game() {
	_view.~shared_ptr();
	_viewModel.~shared_ptr();
	_map.~shared_ptr();
}

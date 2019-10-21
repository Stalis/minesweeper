//
// Created by Stanislav on 20/10/2019.
//

#pragma once

#include "IGameView.hpp"
#include "src/ViewModel/IGameViewModel.hpp"

class CursesGameView : public IGameView {
public:
    CursesGameView(IGameViewModel* viewModel);
    ~CursesGameView() override;

    void draw() override;
    void setCommandCallback(TCommandCallback* callback) override;

private:
	struct CursesWindow;
	CursesWindow* _state;
	int _height = 80;
	int _width = 25;
	int _y = 10;
	int _x = 10;


	IGameViewModel* _viewModel;
	TCommandCallback* _commandCallback;
};



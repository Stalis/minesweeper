//
// Created by Stanislav on 19/10/2019.
//

#pragma once
#include <map>
#include "IGameView.hpp"
#include "../Map/Coordinate.hpp"
#include "../ViewModel/IGameViewModel.hpp"

class ConsoleGameView : public IGameView {
public:
    explicit ConsoleGameView(IGameViewModel* viewModel);
    ~ConsoleGameView() override = default;

    void draw() override;
    void exit();
    void setOpenCallback(TOpenCallback* callback) override;
private:
    std::map<Coordinate, char> _gridView;
    TOpenCallback* _openCell;
    IGameViewModel* _viewModel;
    bool _exit;
    Vector2 cursorPos;
private:
    void input_on();
    void input_off();
};



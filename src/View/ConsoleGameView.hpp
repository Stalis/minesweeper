//
// Created by Stanislav on 19/10/2019.
//

#pragma once
#include <map>
#include "IGameView.hpp"
#include "src/Map/Coordinate.hpp"
#include "src/ViewModel/IGameViewModel.hpp"

class ConsoleGameView : public IGameView {
public:
    explicit ConsoleGameView(IGameViewModel* viewModel);
    ~ConsoleGameView() override = default;

    void draw() override;
    void setCommandCallback(TCommandCallback* callback) override;
    Command waitInput() override;
private:
    std::map<Coordinate, char> _gridView;
    TCommandCallback* _commandCallback;
    IGameViewModel* _viewModel;
};



//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "src/Command.hpp"
#include "IGameViewModel.hpp"
#include "src/Map/IMap.hpp"
#include <memory>

class GameViewModel : public IGameViewModel {
public:
    GameViewModel(std::shared_ptr<IMap> map) : _map(map) {}
    ~GameViewModel() override = default;

    void executeCommand(Command cmd) override;
    TCellMatrix& getCellGrid() override;
    void processGameState(GameState state) override;
    GameState getGameState() override;
private:
    std::shared_ptr<IMap> _map;
    std::unique_ptr<TCellMatrix> _array;
    GameState _state;
    void initCellGrid();
    CellInfo getCellInfo(const Coordinate& coord) const;
	void openCell(int x, int y);
};



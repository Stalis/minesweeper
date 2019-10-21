//
// Created by Stanislav on 19/10/2019.
//

#pragma once

#include "src/Command.hpp"
#include "IGameViewModel.hpp"
#include "src/Map/IMap.hpp"

class GameViewModel : public IGameViewModel {
public:
    GameViewModel(IMap* map) : _map(map) {}
    ~GameViewModel() override = default;

    void executeCommand(Command cmd) override;
    TCellMatrix& getCellGrid() override;
    void movePointer(const Vector2& pos) override;
    void processGameState(GameState state) override;
private:
    IMap* _map;
    TCellMatrix* _array;
    void initCellGrid();
    CellInfo getCellInfo(const Coordinate& coord) const;
	void openCell(int x, int y);
};



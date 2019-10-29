//
// Created by Stanislav on 28/10/2019.
//

#pragma once

#include "src/Map/IMap.hpp"
#include "src/Model/IGameModel.hpp"
#include <memory>

class GameModel : public IGameModel {
public:
    explicit GameModel(const IMap& map);
    void executeCommand(Command cmd) override;
    const TCellMatrix& getCellGrid() const override;
    GameState getGameState() const override;
    bool checkIsWin() const override;
private:
    GameState _state;
    std::unique_ptr<TCellMatrix> _map;

    std::unique_ptr<TCellMatrix> loadMap(const IMap& map) const;
    void openCell(int x, int y);
    void markCell(int x, int y);
    void unmarkCell(int x, int y);
    void setGameState(GameState state);
    void exitGame();
    bool isEndGame() const;
};



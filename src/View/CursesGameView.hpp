//
// Created by Stanislav on 20/10/2019.
//

#pragma once

#include "IGameView.hpp"

class CursesGameView : public IGameView {
public:
    CursesGameView();
    ~CursesGameView() override;

    void draw() override;
    void setOpenCallback(TOpenCallback* callback) override;
};



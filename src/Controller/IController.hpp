//
// Created by Stanislav on 29/10/2019.
//

#pragma once

#include <src/Command.hpp>

class IController {
public:
    virtual Command waitInput() = 0;
    virtual ~IController() = default;
};

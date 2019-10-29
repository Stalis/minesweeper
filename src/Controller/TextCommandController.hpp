//
// Created by Stanislav on 29/10/2019.
//

#pragma once

#include "IController.hpp"
#include <iostream>
#include <utility>

class TextCommandController : public IController {
public:
    using TConverter = std::function<bool(std::string&, int&)>;

    explicit TextCommandController(TConverter c)
        : TextCommandController(std::move(c), std::cin) {}

    TextCommandController(TConverter c, std::istream& is)
        : _converter(std::move(c)), _inputStream(is) {}

    ~TextCommandController() override = default;
    Command waitInput() override;
private:
    TConverter _converter;
    std::istream& _inputStream;

    Command decodeCommand(const std::string&) const;
};



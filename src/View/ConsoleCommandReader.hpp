//
// Created by Stanislav on 28/10/2019.
//

#pragma once

#include <functional>
#include <src/Command.hpp>
#include <utility>

class ConsoleCommandReader {
public:
    using TConverter = std::function<bool(std::string&, int&)>;

    explicit ConsoleCommandReader(TConverter headerConverter)
        : _converter(std::move(headerConverter)) {}

    virtual Command convertToCommand(const std::string& input) const;
private:
    TConverter _converter;
};



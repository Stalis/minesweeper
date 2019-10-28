//
// Created by Stanislav on 28/10/2019.
//

#include "ConsoleCommandReader.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

Command ConsoleCommandReader::convertToCommand(const std::string& input) const {
    if (input.length() == 0) {
        return Command::INVALID;
    }
    std::vector<std::string> words{};
    std::stringstream stream(input);
    {
        std::string word;
        while (std::getline(stream, word, ' ')) {
            words.push_back(word);
        }
    }

    for (auto& word : words) {
        std::cout << word << std::endl;
    }

    if (words.at(0) == "exit") {
        return Command::EXIT;
    }

    int x = -1, y = -1;
    if (words.at(0) == "open") {
        if (_converter(words.at(1), x)) {
            y = std::stoi(words.at(2)) - 1;
            return Command::Open(x, y);
        }
    }

    if (words.size() >= 2) {
        if (words.at(0).length() == 1) {
            if (_converter(words.at(0), x)) {
                y = std::stoi(words.at(1)) - 1;
                return Command::Open(x, y);
            }
        }
    }

    if (words.at(0).length() == 2) {
        auto substr = words.at(0).substr(0, 1);
        if (_converter(substr, x)) {
            y = std::stoi(words.at(0).substr(1, 1)) - 1;
            return Command::Open(x, y);
        }
    }

    return Command::INVALID;
}

//
// Created by Stanislav on 29/10/2019.
//

#include "src/Vector2.hpp"
#include "src/Utils.hpp"
#include "TextCommandController.hpp"
#include <vector>
#include <sstream>

Command TextCommandController::waitInput() {
    std::string input{};
    std::getline(_inputStream, input);
    return decodeCommand(input);
}

static inline Vector2 twoWordsCoord(std::string& first,
                                    std::string& second,
                                    const TextCommandController::TConverter& converter);
static inline Vector2 oneWordCoord(std::string& word, const TextCommandController::TConverter& converter);
static inline Vector2 parseCoord(std::vector<std::string>& words, const TextCommandController::TConverter& converter);
static const Vector2 INVALID_COORD = Vector2{-1, -1};

Command TextCommandController::decodeCommand(const std::string& input) const {
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

    Vector2 res{INVALID_COORD};

    if (words.at(0) == "open" || words.at(0) == "o") {
        auto buf = Utils::tail(words);
        res = parseCoord(buf, _converter);

        if (res != INVALID_COORD) {
            return Command::Open(res.x, res.y);
        }
    }

    if (words.at(0) == "mark" || words.at(0) == "m") {
        auto buf = Utils::tail(words);
        res = parseCoord(buf, _converter);

        if (res != INVALID_COORD) {
            return Command::Mark(res.x, res.y);
        }
    }

    if (words.at(0) == "unmark" || words.at(0) == "um") {
        auto buf = Utils::tail(words);
        res = parseCoord(buf, _converter);

        if (res != INVALID_COORD) {
            return Command::Unmark(res.x, res.y);
        }
    }

    res = parseCoord(words, _converter);
    if (res != INVALID_COORD) {
        return Command::Open(res.x, res.y);
    }

    return Command::INVALID;
}

static inline Vector2 twoWordsCoord(std::string& first,
                                    std::string& second,
                                    const TextCommandController::TConverter& converter) {
    int x = 0, y = 0;
    if (converter(first, x)) {
        try {
            y = std::stoi(second) - 1;
            return Vector2(x, y);
        } catch (std::invalid_argument&) {
        }
    }
    return INVALID_COORD;
}

static inline Vector2 oneWordCoord(std::string& word, const TextCommandController::TConverter& converter) {
    int x = 0, y = 0;
    if (word.length() >= 2) {
        auto substr = word.substr(0, 1);
        if (converter(substr, x)) {
            try {
                y = std::stoi(word.substr(1, 1)) - 1;
                return Vector2(x, y);
            } catch (std::invalid_argument&) {
            }
        }
    }
    return INVALID_COORD;
}

inline Vector2 parseCoord(std::vector<std::string>& words, const TextCommandController::TConverter& converter) {
    auto res = INVALID_COORD;

    if (!words.empty()) {
        res = oneWordCoord(words.at(0), converter);

        if (res == INVALID_COORD && words.size() >= 2) {
            res = twoWordsCoord(words.at(0), words.at(1), converter);
        }
    }
    return res;
}


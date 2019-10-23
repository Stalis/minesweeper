//
// Created by Stanislav on 23/10/2019.
//

#pragma once

class ConsoleColors {
public:
    ConsoleColors() = delete;
    inline static const std::string Black = "\033[0,30m";
    inline static const std::string Red = "\033[0,31m";
    inline static const std::string Green = "\033[0,32m";
    inline static const std::string Yellow = "\033[0,33m";
    inline static const std::string Blue = "\033[0,34m";
    inline static const std::string Magenta = "\033[0,35m";
    inline static const std::string Cyan = "\033[0,36m";
    inline static const std::string White = "\033[0,37m";

    inline static const std::string BrightBlack = "\033[0,90m";
    inline static const std::string BrightRed = "\033[0,91m";
    inline static const std::string BrightGreen = "\033[0,92m";
    inline static const std::string BrightYellow = "\033[0,93m";
    inline static const std::string BrightBlue = "\033[0,94m";
    inline static const std::string BrightMagenta = "\033[0,95m";
    inline static const std::string BrightCyan = "\033[0,96m";
    inline static const std::string BrightWhite = "\033[0,97m";

    inline static const std::string Reset = "\033[0m";
};

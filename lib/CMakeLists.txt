cmake_minimum_required(VERSION 3.12)
project(PDCurses)

file(GLOB SOURCES ./PDCurses/*.c ./PDCurses/common/*.c ./PDCurses/pdcurses/*.c ./PDCurses/wincon/*.c)
file(GLOB HEADERS ./PDCurses/*.h ./PDCurses/common/*.h ./PDCurses/pdcurses/*.h ./PDCurses/wincon/*.h)

message(${SOURCES})

add_library(PDCurses ${SOURCES} ${HEADERS})
target_include_directories(PDCurses
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/PDCurses)
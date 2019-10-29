//
// Created by Stanislav on 20/10/2019.
//

#include "CursesGameView.hpp"
#include <curses.h>
#include <stdexcept>

struct CursesGameView::CursesWindow {
    WINDOW* background;
    WINDOW* decoration;
    WINDOW* overlay;

    void initialize(int sy, int sx, int h, int w, char* label) {
        background = newwin(h, w, sy, sx);
        wattron(background, COLOR_PAIR(7));

        for (int i = w * 0.1; i < w; i++) {
            mvwaddch(background, h - 1, i, ' ');
        }
        for (int i = h * 0.2; i < h; h++) {
            mvwaddch(background, i, w - i, ' ');
        }
        wattroff(background, COLOR_PAIR(7));

        decoration = derwin(background, h - 2, w - 2, 1, 1);
        wbkgd(decoration, COLOR_PAIR(1));

        box(decoration, 0, 0);
        int x, y;
        getmaxyx(decoration, y, x);

        overlay = derwin(decoration, y - 4, x - 2, 3, 1);
        wbkgd(overlay, COLOR_PAIR(1));
        doupdate();
    }
};

CursesGameView::CursesGameView(IGameViewModel* viewModel)
    : _viewModel(viewModel) {
    initscr();
    cbreak();
    raw();
    nonl();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    if (!has_colors()) {
        endwin();
        throw std::runtime_error("Your terminal doesn't support colors")
    }
    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);

    int x, y;
    getmaxyx(stdscr, y, x);
    _state = new CursesWindow{};
    _state->initialize(0, 0, y - 5, x - 5, nullptr);
}

CursesGameView::~CursesGameView() {
}

void CursesGameView::draw() {
    doupdate();
}

void CursesGameView::setCommandCallback(IGameView::TCommandCallback* callback) {
}

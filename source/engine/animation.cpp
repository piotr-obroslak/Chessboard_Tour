#include "engine/animation.h"
#include "engine/except.h"

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define ANIMATION_DELAY (250000)

namespace chessboard_tour
{
    template<typename T>
    T Max(const T & a, const T & b)
    {
        return a > b ? a : b;
    }

    animation::animation()
        : max_row(0)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            initscr();
        );
    }

    animation::~animation()
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            endwin();
        );
    }

    void animation::on_start() /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            nodelay(stdscr, TRUE);
        );
    }

    void animation::on_finish() /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            const auto row = (max_row+1)*2;
            const auto prompt = "press any key to quit";
            mvprintw(row, 0, prompt);
            refresh();
            nodelay(stdscr, FALSE);
            mvgetch(row, strlen(prompt) + 1);
        );
    }

    bool animation::on_is_cancelled() /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            int c = mvgetch(max_row+1, 0);
            if (c == 'q') {
                return true;
            }
        );

        return false;
    }

    void animation::on_advance_to_position(
        const unsigned row, const unsigned col, const unsigned No) /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
             max_row = Max(max_row, row);

             mvprintw(row*2, col*5, "%5d", No);
             refresh();
             usleep(ANIMATION_DELAY);
        );
    }

    void animation::on_backtrack_from_position(
        const unsigned row, const unsigned col, const unsigned No) /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
             max_row = Max(max_row, row);

             mvprintw(row*2, col*5, "     ");
             refresh();
             usleep(ANIMATION_DELAY);
        );
    }
}

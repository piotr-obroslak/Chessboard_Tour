#include "engine/animation.h"
#include "engine/except.h"

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define ANIMATION_DELAY_MICRO_SECONDS (150000)

namespace chessboard_tour
{
    template<typename T>
    T Max(const T & a, const T & b)
    {
        return a > b ? a : b;
    }

    animation::animation()
        : ranks(0)
		, files(0)
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

    void animation::on_start(const unsigned r, const unsigned f) /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
		 	ranks = r;
			files = f;

            nodelay(stdscr, TRUE);

			start_color();
			init_pair(1, COLOR_CYAN, COLOR_BLACK);
			init_pair(2, COLOR_RED, COLOR_BLACK);

			auto file_guide = [](const unsigned rank, const unsigned file)
			{
				const auto r = rank*4+1;
				const auto f = file*9;

		 		attron(COLOR_PAIR(2));
				mvaddch(r, f, '+');
				mvaddch(r+4, f, '+');
		 		attroff(COLOR_PAIR(2));

				for (auto i=1; i<=3; i++)
				{
		 			attron(COLOR_PAIR(2));
					mvaddch(r+i, f, '|');
		 			attroff(COLOR_PAIR(2));
				}
			};

			auto rank_guide = [](const unsigned rank, const unsigned file, const bool filled = true)
			{
				const auto r = rank*4+1;
				const auto f = file*9;

				for (auto i=1; i<=8; i++)
				{
		 			attron(COLOR_PAIR(2));
					mvaddch(r, f+i, '-');
		 			attroff(COLOR_PAIR(2));
				}
			
				if (filled)
				{
					if ((file%2!=0) && (rank%2==0) || ((file%2==0) && (rank%2!=0)))
					{
						for (auto i=1; i<=8; i++)
						{
							mvaddch(r+1, f+i, '@');
							mvaddch(r+3, f+i, '@');
						}
						mvaddch(r+2, f+1, '@');
						mvaddch(r+2, f+2, '@');
						mvaddch(r+2, f+7, '@');
						mvaddch(r+2, f+8, '@');
					}
				}
			};

			for (auto r=0U; r<ranks; r++)
			{
				for (auto f=1U; f<=files; f++)
				{
					file_guide(r, f);
					rank_guide(r, f);
				}
			
				file_guide(r, files+1);
			}

			for (auto f=1U; f<=files; f++)
			{
				rank_guide(ranks, f, false);
			}
			
			refresh();
            usleep(ANIMATION_DELAY_MICRO_SECONDS);
        );
    }

    void animation::on_finish() /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            const auto row = (ranks+1)*4;
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
            int c = mvgetch(ranks+1, 0);
            if (c == 'q') {
                return true;
            }
        );

        return false;
    }

    void animation::on_advance_to_position(
        const unsigned rank, const unsigned file, const unsigned No) /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
		 	attron(COLOR_PAIR(1));
            mvprintw(rank*4-1, file*9+3, "%3d", No);
			attroff(COLOR_PAIR(1));
            refresh();
            usleep(ANIMATION_DELAY_MICRO_SECONDS);
        );
    }

    void animation::on_backtrack_from_position(
        const unsigned rank, const unsigned file, const unsigned No) /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
		 	attron(COLOR_PAIR(1));
            mvprintw(rank*4-1, file*9+3, "   ");
			attroff(COLOR_PAIR(1));
            refresh();
            usleep(ANIMATION_DELAY_MICRO_SECONDS);
        );
    }
}

#include "engine/engine.h"
#include "engine/except.h"


#include <iostream>
#include <stack>
#include <vector>

#define USE_WARNSDORFS_HEURISTIC    (1)

namespace chessboard_tour
{
    class engine::impl
    {
    public:
        engine::result solve(
            const unsigned rows, const unsigned columns,
            const unsigned from_row, const unsigned from_col,
            i_chessman & chessman,
            i_consumer & consumer);

    private:
        struct chessboard
            : public std::vector<std::vector<unsigned>>
        {
        public:
            chessboard(const unsigned rows, const unsigned columns)
            {
                CHESSBOARD_TOUR_EXCEPTION_SECURE
                (
                    resize(rows, std::vector<unsigned>(columns, 0));
                );
            }

            const unsigned rows()
            {
                CHESSBOARD_TOUR_EXCEPTION_SECURE
                (
                    return size();
                );
            }

            const unsigned columns()
            {
                CHESSBOARD_TOUR_EXCEPTION_SECURE
                (
                    return this->operator[](0).size();
                );
            }
        };

        struct jump
        {
            jump(const signed r, const signed c, const unsigned opts)
                : row(r), column(c), No(1), opt(opts)
            {
#if USE_WARNSDORFS_HEURISTIC
                considered.resize(opts, false);
#endif
            }
/*
            jump(const jump &that)
                : jump(that.row, that.column, that.opt), No(that)
            {

            }*/

            bool next(
                chessboard & cb,
                const i_chessman & chessman,
                jump & next)
            {
                CHESSBOARD_TOUR_EXCEPTION_SECURE
                (
#if USE_WARNSDORFS_HEURISTIC
                    unsigned best = chessman.move_No();
                    unsigned best_idx = chessman.move_No();
                    for (unsigned mv=0; mv<chessman.move_No(); mv++)
                    {
                        const auto move = chessman.at(mv);
                        const auto next_row = row + move.dr;
                        const auto next_column = column + move.dc;
                        //std::cout << "analyzing: " << next_row+1 << " " << next_column+1 << std::endl;

                        if (considered[mv])
                        {
                            //std::cout << "\talready analyzed" << std::endl;
                            continue;
                        }

                        if (next_row < 0 || next_row >= static_cast<signed>(cb.rows()) ||
                            next_column < 0 || next_column >= static_cast<signed>(cb.columns()))
                        {
                            //std::cout << "\tout of chessboard" << std::endl;
                            continue;
                        }

                        if (cb[next_row][next_column] != 0)
                        {
                            //std::cout << "\ttaken previously" << std::endl;
                            continue;
                        }

                        unsigned options = 0;
                        for (unsigned mv2=0; mv2<chessman.move_No(); mv2++)
                        {
                            const auto move2 = chessman.at(mv2);
                            const auto next_row2 = next_row + move2.dr;
                            const auto next_column2 = next_column + move2.dc;

                            if (next_row2 < 0 || next_row2 >= static_cast<signed>(cb.rows()) ||
                                next_column2 < 0 || next_column2 >= static_cast<signed>(cb.columns()) ||
                                cb[next_row2][next_column2] != 0)
                            {
                                continue;
                            }

                            options++;
                        }
                        
                        //std::cout << "\tpossible moves " << options << std::endl;

                        if (options < best)
                        {
                            best = options;
                            best_idx = mv;
                        }
                    }

                    if (best_idx < chessman.move_No())
                    {
                        const auto move = chessman.at(best_idx);
                        const auto next_row = row + move.dr;
                        const auto next_column = column + move.dc;

                        next.row = next_row;
                        next.column = next_column;
                        next.No = No + 1;

                        //std::cout << "\tfinally choosen: " << next_row+1 << " " << next_column+1 << std::endl;
                        considered[best_idx] = true;
                        return true;
                    }
#else
                    while (opt > 0)
                    {
                        const auto move = chessman.at(chessman.move_No() - opt);
                        const auto next_row = row + move.dr;
                        const auto next_column = column + move.dc;

                        if (next_row < 0 || next_row >= static_cast<signed>(cb.rows()) ||
                            next_column < 0 || next_column >= static_cast<signed>(cb.columns()))
                        {
                            opt--;
                            continue;
                        }

                        if (cb[next_row][next_column] != 0)
                        {
                            opt--;
                            continue;
                        }

                        next.row = next_row;
                        next.column = next_column;
                        next.No = No + 1;
                        next.opt = chessman.move_No();

                        opt--;
                        return true;
                    }
#endif
                );

                return false;
            }

            signed row;
            signed column;
            unsigned No;
            unsigned opt;

#if USE_WARNSDORFS_HEURISTIC
            std::vector<bool> considered;
#endif
        };
    };

    engine::result engine::impl::solve(
        const unsigned rows, const unsigned columns,
        const unsigned from_row, const unsigned from_col,
        i_chessman & chessman,
        i_consumer & consumer)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            result r = result::unsolvable;

            chessboard cb(rows, columns);

            std::stack<jump> s;
            s.push(jump(from_row-1, from_col-1, chessman.move_No()));

            const auto expected_jump_No = cb.rows() * cb.columns();

            while (!s.empty())
            {
                if (consumer.on_is_cancelled())
                {
                    r = result::cancelled;
                    break;
                }

                auto & curr = s.top();
                cb[curr.row][curr.column] = curr.No;
                consumer.on_advance_to_position(curr.row+1, curr.column+1, curr.No);

                if (cb[curr.row][curr.column] == expected_jump_No)
                {
                    r = result::solved;
                    break;
                }

                jump next(curr.row, curr.column, chessman.move_No());
                if (curr.next(cb, chessman, next))
                {
                    // there is a possible move... forward
                    s.push(next);
                }
                else
                {
                    // no move is possible... backtrack
                    s.pop();

                    cb[curr.row][curr.column] = 0;
                    consumer.on_backtrack_from_position(curr.row+1, curr.column+1, curr.No);
                }
            }

            return r;
        );

        return result::unsolvable;
    }


    engine::engine()
        : pimpl(nullptr)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
             pimpl.reset(new impl());
        );
    }

    engine::~engine()
    {
    }

    engine::result engine::solve(
        const unsigned rows, const unsigned columns,
        const unsigned from_row, const unsigned from_col,
        i_chessman & chessman,
        i_consumer & consumer)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            consumer.on_start();
            
            const auto r = pimpl->solve(rows, columns, from_row, from_col, chessman, consumer);

            consumer.on_finish();

            return r;
        );

        return result::unsolvable;
    }
}

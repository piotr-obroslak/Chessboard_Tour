#include "engine/except.h"
#include "engine/superqueen.h"

#include <vector>

namespace chessboard_tour
{
    class superqueen::impl
    {
        friend class superqueen;

        static const std::vector<i_chessman::move> moves;
    };

    /*static*/ const std::vector<i_chessman::move> superqueen::impl::moves = 
    {
        /* a regular queen would of course traverse the whole chessboard in linear time
         * for the one described below it won't be so easy...
         * */
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {2, 2}, {2, 0}, {2, -2}, {0, -2}
    };

    superqueen::superqueen()
        : pimpl(nullptr)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
             pimpl.reset(new impl());
        );
    }

    superqueen::~superqueen()
    {
    }

    unsigned superqueen::move_No() const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->moves.size();
        );

        return 0;
    }

    i_chessman::move superqueen::at(const unsigned idx) const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->moves[idx];
        );

        return {0, 0};
    }
}

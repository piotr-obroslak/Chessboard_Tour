#include "engine/except.h"
#include "engine/superking.h"

#include <vector>

namespace chessboard_tour
{
    class superking::impl
    {
        friend class superking;

        static const std::vector<i_chessman::move> moves;
    };

    /*static*/ const std::vector<i_chessman::move> superking::impl::moves = 
    {
        /* a regular queen would of course traverse the whole chessboard in linear time
         * for the one described below it won't be so easy...
         * */
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {2, 2}, {2, 0}, {2, -2}, {0, -2}
    };

    superking::superking()
        : pimpl(nullptr)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
             pimpl.reset(new impl());
        );
    }

    superking::~superking()
    {
    }

    unsigned superking::move_No() const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->moves.size();
        );

        return 0;
    }

    i_chessman::move superking::at(const unsigned idx) const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->moves[idx];
        );

        return {0, 0};
    }
}

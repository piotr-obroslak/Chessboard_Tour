#include "engine/except.h"
#include "engine/knight.h"

#include <vector>

namespace chessboard_tour
{
    class knight::impl
    {
    public:
        static const std::vector<i_chessman::move> opts; 
    };

    /*static*/ const std::vector<i_chessman::move> knight::impl::opts =
    {
        {2, 1}, {1, 2}, {-1,2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };
    
    knight::knight()
        : pimpl(nullptr)
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            pimpl.reset(new impl());
        );
    }

    knight::~knight()
    {
    }

    unsigned knight::move_No() const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->opts.size();
        );

        return 0;
    }

    i_chessman::move knight::at(const unsigned idx) const /*override*/
    {
        CHESSBOARD_TOUR_EXCEPTION_SECURE
        (
            return pimpl->opts[idx];
        );

        return {0, 0};
    }

}

#ifndef __KT_ANIMATION__
#define __KT_ANIMATION__

#include "engine/engine.h"

namespace chessboard_tour
{
    class animation
        : public i_consumer
    {
    public:
        animation();
        ~animation();

        void on_start() override;
        void on_finish() override;
        bool on_is_cancelled() override;
        void on_advance_to_position(
            const unsigned row, const unsigned col, const unsigned No) override;
        void on_backtrack_from_position(
            const unsigned row, const unsigned col, const unsigned No) override;

    private:
        unsigned max_row;
    };
}

#endif

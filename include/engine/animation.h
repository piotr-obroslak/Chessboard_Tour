#ifndef __CT_ANIMATION__
#define __CT_ANIMATION__

#include "engine/engine.h"

namespace chessboard_tour
{
    class animation
        : public i_consumer
    {
    public:
        animation();
        ~animation();

        void on_start(const unsigned ranks, const unsigned files) override;
        void on_finish() override;
        bool on_is_cancelled() override;
        void on_advance_to_position(
            const unsigned rank, const unsigned file, const unsigned No) override;
        void on_backtrack_from_position(
            const unsigned rank, const unsigned file, const unsigned No) override;

    private:
		unsigned ranks;
		unsigned files;
    };
}

#endif

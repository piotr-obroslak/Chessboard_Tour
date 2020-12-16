#ifndef __CT_STORYTELLER_H__
#define __CT_STORYTELLER_H__

#include "engine/engine.h"

namespace chessboard_tour
{
    class storyteller
        : public i_consumer
    {
        void on_start(const unsigned ranks, const unsigned files) override;
        void on_finish() override;
        bool on_is_cancelled() override;
        void on_advance_to_position(
            const unsigned rank, const unsigned file, const unsigned No) override;
        void on_backtrack_from_position(
            const unsigned rank, const unsigned file, const unsigned No) override;
    };
}

#endif

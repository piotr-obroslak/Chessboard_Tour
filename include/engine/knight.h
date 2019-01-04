#ifndef __CT_KNIGHT_H__
#define __CT_KNIGHT_H__

#include "engine/engine.h"

#include <memory>

namespace chessboard_tour
{
    class knight
        : public i_chessman
    {
    public:
        knight();
        ~knight();

        unsigned move_No() const override;
        move at(const unsigned idx) const override;

    private:
        class impl;
        std::unique_ptr<impl> pimpl;
    };
}

#endif

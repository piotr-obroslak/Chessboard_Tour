#ifndef __CT_SUPERKING_H__
#define __CT_SUPERKING_H__

#include "engine/engine.h"

#include <memory>

namespace chessboard_tour
{
    class superking
        : public i_chessman
    {
    public:
        superking();
        ~superking();

        unsigned move_No() const override;
        move at(const unsigned idx) const override;

    private:
        class impl;
        std::unique_ptr<impl> pimpl;
    };
}

#endif

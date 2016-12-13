#ifndef __KT_SUPERQUEEN_H__
#define __KT_SUPERQUEEN_H__

#include "engine/engine.h"

#include <memory>

namespace chessboard_tour
{
    class superqueen
        : public i_chessman
    {
    public:
        superqueen();
        ~superqueen();

        unsigned move_No() const override;
        move at(const unsigned idx) const override;

    private:
        class impl;
        std::unique_ptr<impl> pimpl;
    };
}

#endif
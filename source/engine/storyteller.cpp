#include "engine/except.h"
#include "engine/storyteller.h"

#include <iostream>

namespace chessboard_tour
{
    void storyteller::on_start() /*override*/
    {

    }

    void storyteller::on_finish() /*override*/
    {
    }

    bool storyteller::on_is_cancelled() /*override*/
    {
        return false;
    }

    void storyteller::on_advance_to_position(
        const unsigned row, const unsigned column, const unsigned No) /*override*/
    {
        std::cout << "fwd: " << "<" << row << "," << column << ">" << " @ " << No << std::endl;
    }

    void storyteller::on_backtrack_from_position(
        const unsigned row, const unsigned column, const unsigned No) /*override*/
    {
        std::cout << "rev: " << "<" << row << "," << column << ">" << " @ " << No << std::endl;
    }
}

#include "engine/except.h"
#include "engine/storyteller.h"

#include <iostream>

namespace chessboard_tour
{
    void storyteller::on_start(const unsigned ranks, const unsigned files) /*override*/
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
        const unsigned rank, const unsigned file, const unsigned No) /*override*/
    {
        std::cout << "fwd: " << "<" << rank << "," << file << ">" << " @ " << No << std::endl;
    }

    void storyteller::on_backtrack_from_position(
        const unsigned rank, const unsigned file, const unsigned No) /*override*/
    {
        std::cout << "rev: " << "<" << rank << "," << file << ">" << " @ " << No << std::endl;
    }
}

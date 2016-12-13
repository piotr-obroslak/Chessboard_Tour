#include "engine/except.h"

namespace chessboard_tour
{
    exception::exception(const std::string & what_arg)
        : whatstr(what_arg)
    {
    }

    exception::exception(const char * what_arg)
        : exception(std::string(what_arg))
    {
    }

    const char * exception::what() const noexcept
    {
        return whatstr.c_str();
    }
}

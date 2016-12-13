#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <stdexcept>
#include <sstream>

namespace chessboard_tour
{
    class exception
        : public std::exception
    {
    public:
        explicit exception(const std::string & what_arg);
        explicit exception(const char * what_arg);

        const char * what() const noexcept;

    private:
        std::string whatstr;
    };
}

#define CHESSBOARD_TOUR_EXCEPTION_RETHROW(e)               \
    std::stringstream stream;                           \
    stream << e.what() << "\n\t@" << __PRETTY_FUNCTION__\
        << " (" << __FILE__ << ":" << __LINE__ << ")";  \
    throw chessboard_tour::exception(stream.str())

#define CHESSBOARD_TOUR_EXCEPTION_SECURE(code)         \
    try {                                           \
        code                                        \
    } catch (chessboard_tour::exception & e) {         \
        CHESSBOARD_TOUR_EXCEPTION_RETHROW(e);          \
    } catch (std::exception & e) {                  \
        CHESSBOARD_TOUR_EXCEPTION_RETHROW(e);          \
    } catch(...) {                                  \
        throw chessboard_tour::exception("unexpected");\
    }if (false)

#endif

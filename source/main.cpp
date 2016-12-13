#include "engine/animation.h"
#include "engine/engine.h"
#include "engine/except.h"
#include "engine/knight.h"
#include "engine/storyteller.h"

#include <iostream>

int main(int argc, char * argv[])
{
    using exception = chessboard_tour::exception;
    using knight = chessboard_tour::knight;
    using engine = chessboard_tour::engine;
    using animation = chessboard_tour::animation;
    using storyteller = chessboard_tour::storyteller;

    try
    {
        animation consumer;
        //storyteller consumer;
        knight kn;
        const auto result = engine().solve(16, 16, 9, 8, kn, consumer);
    }
    catch (exception & e)
    {
        std::cout << "EXCEPTION:\t" << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "!unexpected!" << std::endl;
    }

    return 0;
}

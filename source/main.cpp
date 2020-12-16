#include "engine/animation.h"
#include "engine/engine.h"
#include "engine/except.h"
#include "engine/knight.h"
#include "engine/storyteller.h"
#include "engine/superking.h"

#include <iostream>

int main(int argc, char * argv[])
{
    using exception = chessboard_tour::exception;
    using engine = chessboard_tour::engine;

    try
    {
        using animation = chessboard_tour::animation;
        animation consumer;

        //using storyteller = chessboard_tour::storyteller;
        //storyteller consumer;

        using knight = chessboard_tour::knight;
        knight kn;
        engine().solve(8, 8, 2, 2, kn, consumer);

        //using superking = chessboard_tour::superking;
        //superking sk;
        //engine().solve(5, 5, 1, 1, sk, consumer);
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

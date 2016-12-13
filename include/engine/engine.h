#ifndef __KT_ENGINE_H__
#define __KT_ENGINE_H__

#include <iostream>
#include <memory>

namespace chessboard_tour
{
    class i_consumer
    {
    public:
        virtual void on_start() = 0;
        virtual void on_finish() = 0;
        virtual bool on_is_cancelled() = 0;
        virtual void on_advance_to_position(
            const unsigned row, const unsigned column, const unsigned No) = 0;
        virtual void on_backtrack_from_position(
            const unsigned row, const unsigned column, const unsigned No) = 0;
    };


/*    class i_chessboard
    {
    public:
        virtual unsigned rows() const = 0;
        virtual unsigned columns() const = 0;
        virtual unsigned & at(
            const unsigned row, const unsigned column) = 0;

        const unsigned & at(
            const unsigned row, const unsigned column) const
        {
            return const_cast<i_chessboard&>(*this).at(row, column);
        }
    };*/
    

    class i_chessman
    {
    public:
        struct move
        {
            signed dr;
            signed dc;
        };

        virtual unsigned move_No() const = 0;
        virtual move at(const unsigned idx) const = 0;
    };


    class engine
    {
    public:
        engine();
        ~engine();

        static const unsigned MAX_CHESSBOARD_SIZE   = 16 * 16;

        enum class result
        {
            solved,
            unsolvable,
            cancelled
        };

        result solve(
            //i_chessboard & chessboard,
            const unsigned rows, const unsigned columns,
            const unsigned from_row, const unsigned from_col,
            i_chessman & chessman,
            i_consumer & consumer);

    private:
        class impl;
        std::unique_ptr<impl> pimpl;
    };
}

#endif

#ifndef BITBOARDWRAPPER_H
#define BITBOARDWRAPPER_H

#include "bitboard.h"

template <std::size_t WIDTH, std::size_t HEIGHT>
class BitBoardWrapper
{
public:
    enum struct CELL
    {
        EMPTY = 0,
        QUEEN = 1,
        ATTACKED = 2
    };
public:
    void setValue(const std::size_t x, const std::size_t y, const CELL value)
    {
        if(value == CELL::ATTACKED)
            m_attacks.setBit(x, y, 1);
        else if(value == CELL::QUEEN)
            m_queens.setBit(x, y, 1);
        else if(value == CELL::EMPTY)
        {
            m_queens.setBit(x, y, 0);
            m_attacks.setBit(x, y, 0);
        }
    }

    CELL getValue(const std::size_t x, const std::size_t y) const
    {
        if(m_attacks.getBit(x, y))
            return CELL::ATTACKED;
        else if(m_queens.getBit(x, y))
            return CELL::QUEEN;
        return CELL::EMPTY;
    }

    std::size_t width() const
    {
        return WIDTH;
    }

    std::size_t height() const
    {
        return HEIGHT;
    }
private:
    BitBoard<WIDTH, HEIGHT> m_queens;
    BitBoard<WIDTH, HEIGHT> m_attacks;
};

#endif

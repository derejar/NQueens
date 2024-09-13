#ifndef BITSETWRAPPER_H
#define BITSETWRAPPER_H

#include <bitset>

template <std::size_t WIDTH, std::size_t HEIGHT>
class BitsetWrapper
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
            m_attacks.set(y*WIDTH + x, 1);
        else if(value == CELL::QUEEN)
            m_queens.set(y*WIDTH + x, 1);
        else if(value == CELL::EMPTY)
        {
            m_queens.set(y*WIDTH + x, 0);
            m_attacks.set(y*WIDTH + x, 0);
        }
    }

    CELL getValue(const std::size_t x, const std::size_t y) const
    {
        if(m_attacks[y*WIDTH + x])
            return CELL::ATTACKED;
        else if(m_queens[y*WIDTH + x])
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
    std::bitset<WIDTH*HEIGHT> m_queens;
    std::bitset<WIDTH*HEIGHT> m_attacks;
};

#endif

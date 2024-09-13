#ifndef ARRAYBOARDWRAPPER_H
#define ARRAYBOARDWRAPPER_H

#include <array>
#include <cstddef>

template <std::size_t WIDTH, std::size_t HEIGHT>
class ArrayBoardWrapper
{
public:
    enum class CELL : std::uint_fast8_t
    {
        EMPTY = 0,
        QUEEN = 1,
        ATTACKED = 2
    };
public:
    void setValue(const std::size_t x, const std::size_t y, const CELL value)
    {
        m_array[y*WIDTH + x] = value;
    }

    CELL getValue(const std::size_t x, const std::size_t y) const
    {
        return m_array[y*WIDTH + x];
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
    std::array<CELL, WIDTH*HEIGHT> m_array;
};

#endif

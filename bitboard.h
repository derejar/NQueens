#ifndef BITBOARD_H
#define BITBOARD_H

#include <utility>
#include <cstdint>
#include <type_traits>
#include <stdexcept>

namespace details
{
    template <typename T>
    struct tag
    {
        using type = T;
    };

    template <std::size_t WIDTH, std::size_t HEIGHT, typename...>
    struct min_uint
    {
        using type = std::uint_fast8_t[WIDTH*HEIGHT / (8*sizeof(std::uint_fast8_t)) +
                                        static_cast<bool>(WIDTH*HEIGHT % (8*sizeof(std::uint_fast8_t)))];
    };

    template <std::size_t WIDTH, std::size_t HEIGHT, typename T, typename... Ts>
    struct min_uint<WIDTH, HEIGHT, T, Ts...> :  std::conditional<WIDTH*HEIGHT <= 8*sizeof(T),
                                                    tag<T>,
                                                    min_uint<WIDTH, HEIGHT, Ts...>
                                                >::type
    {};

    template <std::size_t WIDTH, std::size_t HEIGHT>
    using board_t = typename min_uint<WIDTH, HEIGHT, std::uint_fast8_t,
                                                     std::uint_fast16_t,
                                                     std::uint_fast32_t,
                                                     std::uint_fast64_t,
                                                     std::uintmax_t
                                                >::type;
}

template <std::size_t WIDTH, std::size_t HEIGHT, bool = (WIDTH*HEIGHT <= (8*sizeof(std::uintmax_t)))>
class BitBoard;





template <std::size_t WIDTH, std::size_t HEIGHT>
class BitBoard<WIDTH, HEIGHT, true>
{
public:
    BitBoard(const details::board_t<WIDTH, HEIGHT>& board = 0);
    void setBit(const std::size_t x, const std::size_t y, const bool value);
    bool getBit(const std::size_t x, const std::size_t y) const;
private:
    details::board_t<WIDTH, HEIGHT> m_board;
};

template <std::size_t WIDTH, std::size_t HEIGHT>
BitBoard<WIDTH, HEIGHT, true>::BitBoard(const details::board_t<WIDTH, HEIGHT>& board) : m_board(board)
{}

template <std::size_t WIDTH, std::size_t HEIGHT>
void BitBoard<WIDTH, HEIGHT, true>::setBit(const std::size_t x, const std::size_t y, const bool value)
{
    if(x >= WIDTH || y >= HEIGHT)
        throw std::runtime_error("Incorrect x or y coordinates!");
    details::board_t<WIDTH, HEIGHT> number = details::board_t<WIDTH, HEIGHT>(1) << ((WIDTH - x - 1) + y*WIDTH);
    if(value)
        m_board |= number;
    else
    {
        number ^= ~details::board_t<WIDTH, HEIGHT>(0);
        m_board &= number;
    }
}

template <std::size_t WIDTH, std::size_t HEIGHT>
bool BitBoard<WIDTH, HEIGHT, true>::getBit(const std::size_t x, const std::size_t y) const
{
    if(x >= WIDTH || y >= HEIGHT)
        throw std::runtime_error("Incorrect x or y coordinates!");
    return (m_board >> ((WIDTH - x - 1) + y*WIDTH)) & true;
}





template <std::size_t WIDTH, std::size_t HEIGHT>
class BitBoard<WIDTH, HEIGHT, false>
{
public:
    BitBoard(const details::board_t<WIDTH, HEIGHT>& board = {0});
    void setBit(const std::size_t x, const std::size_t y, const bool value);
    bool getBit(const std::size_t x, const std::size_t y) const;
private:
    details::board_t<WIDTH, HEIGHT> m_board = {0};
};

template <std::size_t WIDTH, std::size_t HEIGHT>
BitBoard<WIDTH, HEIGHT, false>::BitBoard(const details::board_t<WIDTH, HEIGHT>& board)
{
    std::size_t i =0;
    const std::size_t SIZE = sizeof(m_board) / sizeof(std::uint_fast8_t);
    while(i < SIZE)
    {
        m_board[i] = board[i];
        ++i;
    }
}

template <std::size_t WIDTH, std::size_t HEIGHT>
void BitBoard<WIDTH, HEIGHT, false>::setBit(const std::size_t x, const std::size_t y, const bool value)
{
    if(x >= WIDTH || y >= HEIGHT)
        throw std::runtime_error("Incorrect x or y coordinates!");
    std::size_t index = x + (HEIGHT - y - 1)*WIDTH;
    std::size_t cellSize = 8*sizeof(std::uint_fast8_t);
    long long i = index / cellSize;
    std::size_t j = (8*sizeof(std::uint_fast8_t) - 1) - index % cellSize;
    std::uint_fast8_t number = std::uint_fast8_t(1) << (j);
    if(value)
        m_board[i] |= number;
    else
    {
        number ^= ~uint_fast8_t(0);
        m_board[i] &= number;
    }
}

template <std::size_t WIDTH, std::size_t HEIGHT>
bool BitBoard<WIDTH, HEIGHT, false>::getBit(const std::size_t x, const std::size_t y) const
{
    if(x >= WIDTH || y >= HEIGHT)
        throw std::runtime_error("Incorrect x or y coordinates!");
    std::size_t index = x + (HEIGHT - y - 1)*WIDTH;
    std::size_t cellSize = 8*sizeof(std::uint_fast8_t);
    long long i = index / cellSize;
    std::size_t j = (8*sizeof(std::uint_fast8_t) - 1) - index % cellSize;
    return (m_board[i] >> j) & true;
}

#endif

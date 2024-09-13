#ifndef BITBOARDTESTS_H
#define BITBOARDTESTS_H
#include "bitboard.h"
#include <stdexcept>

#define TEST(function) \
if(!function()) \
    throw std::runtime_error(std::string(#function) + "() failed!");

class BitBoardTests
{
public:
    bool testAll() const;
    bool testSetBit() const;
    bool testGetBit() const;
private:
    bool testSetBitOneNumber() const;
    bool testSetBitArray() const;
    bool testGetBitOneNumber() const;
    bool testGetBitArray() const;
};

template <std::size_t WIDTH, std::size_t HEIGHT, bool IS_ARRAY>
bool operator==(const BitBoard<WIDTH, HEIGHT, IS_ARRAY>& lhs, const BitBoard<WIDTH, HEIGHT, IS_ARRAY>& rhs)
{
    for(std::size_t i = 0; i < WIDTH; ++i)
        for(std::size_t j = 0; j < HEIGHT; ++j)
            if(lhs.getBit(i, j) != rhs.getBit(i, j))
                return false;
    return true;
}

template <std::size_t WIDTH, std::size_t HEIGHT, bool IS_ARRAY>
bool operator!=(const BitBoard<WIDTH, HEIGHT, IS_ARRAY>& lhs, const BitBoard<WIDTH, HEIGHT, IS_ARRAY>& rhs)
{
    return !(lhs == rhs);
}

bool BitBoardTests::testAll() const
{
    TEST(testSetBit);
    TEST(testGetBit);
    return true;
}

bool BitBoardTests::testSetBit() const
{
    TEST(testSetBitOneNumber);
    TEST(testSetBitArray);
    return true;
}

bool BitBoardTests::testGetBit() const
{
    TEST(testGetBitOneNumber);
    TEST(testGetBitArray);
    return true;
}

bool BitBoardTests::testSetBitOneNumber() const
{
    BitBoard<4, 8> board1;
    board1.setBit(3, 4, 1);
    BitBoard<4, 8> expected1(0x0001'0000);
    if(board1 != expected1)
        return false;

    board1.setBit(2, 3, 1);
    BitBoard<4, 8> expected2(0x0001'2000);
    if(board1 != expected2)
        return false;

    board1.setBit(2, 3, 0);
    if(board1 != expected1)
        return false;

    BitBoard<8, 8> board2;
    board2.setBit(6, 4, 1);
    BitBoard<8, 8> expected3(0x0000'0002'0000'0000);
    if(board2 != expected3)
        return false;

    board2.setBit(7, 7, 1);
    BitBoard<8, 8> expected4(0x0100'0002'0000'0000);
    if(board2 != expected4)
        return false;

    return true;
}

bool BitBoardTests::testSetBitArray() const
{
    BitBoard<9, 9> board1;
    board1.setBit(3, 5, 1);
    BitBoard<9, 9> expected1({{0x00}, {0x00}, {0x00}, {0x02}});
    if(board1 != expected1)
        return false;

    BitBoard<6, 14> board2;
    board2.setBit(0, 13, 1);
    BitBoard<6, 14> expected2({{0x80}});
    if(board2 != expected2)
        return false;

    board2.setBit(5, 0, 1);
    BitBoard<6, 14> expected3({{0x80}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x10}});
    if(board2 != expected3)
        return false;

    board2.setBit(1, 9, 1);
    BitBoard<6, 14> expected4({{0x80}, {0x00}, {0x00}, {0x40}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x10}});
    if(board2 != expected4)
        return false;

    board2.setBit(1, 9, 0);
    board2.setBit(5, 0, 0);
    if(board2 != expected2)
        return false;
    return true;
}

bool BitBoardTests::testGetBitOneNumber() const
{
    BitBoard<4, 8> board1(0x0001'0000);
    if(board1.getBit(3, 4) != true)
        return false;
    if(board1.getBit(2, 0) != false)
        return false;
    return true;
}

bool BitBoardTests::testGetBitArray() const
{
    BitBoard<6, 14> board1({{0x80}, {0x00}, {0x00}, {0x40}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x00}, {0x10}});
    if(board1.getBit(5, 0) != true)
        return false;
    if(board1.getBit(4, 7) != false)
        return false;
    return true;
}

#endif

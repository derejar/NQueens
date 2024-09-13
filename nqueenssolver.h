#ifndef NQUEENSSOLVER_H
#define NQUEENSSOLVER_H

#include <cstddef>
#include <vector>

template <typename Board>
class NQueensSolver
{
public:
    using CELL = typename Board::CELL;
public:
    std::vector<Board> solve(const std::size_t queensCount) const
    {
        std::vector<Board> solutions;
        solve(solutions, Board(), queensCount);
        return solutions;
    }
private:
    Board setQueen(Board board, const std::size_t x, const std::size_t y) const
    {
        std::size_t minorDiagonalX = x - std::min(x, y);
        std::size_t minorDiagonalY = y - std::min(x, y);
        long long mainDiagonalX = x + std::min(board.width()- 1 - x, y);
        std::size_t mainDiagonalY = y - std::min(board.width() - 1 - x, y);
        for(std::size_t i = 0; i < board.width(); ++i)
        {
            board.setValue(x, i, CELL::ATTACKED);
            board.setValue(i, y, CELL::ATTACKED);
            if(minorDiagonalX < board.width() && minorDiagonalY < board.height())
                board.setValue(minorDiagonalX++, minorDiagonalY++, CELL::ATTACKED);
            if(mainDiagonalX >= 0 && mainDiagonalY < board.height())
                board.setValue(mainDiagonalX--, mainDiagonalY++, CELL::ATTACKED);
        }
        board.setValue(x, y, CELL::QUEEN);
        return board;
    }

    void solve(std::vector<Board>& solutions, const Board& board, const std::size_t queensCount) const
    {
        if(!queensCount)
        {
            solutions.push_back(board);
            return;
        }
        std::size_t x = board.width() - queensCount;
        for(std::size_t y = 0; y < board.height(); ++y)
            if(board.getValue(x, y) != CELL::ATTACKED && board.getValue(x, y) != CELL::QUEEN)
                solve(solutions, setQueen(board, x, y), queensCount - 1);
    }
};


#endif

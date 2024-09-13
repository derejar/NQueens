#include "bitboardtests.h"
#include "nqueenssolver.h"
#include "arrayboardwrapper.h"
#include "bitboardwrapper.h"
#include "bitsetwrapper.h"
#include "stopwatch.h"
#include <iostream>

template <typename Board, std::size_t COUNT>
void test(std::string_view str, const std::size_t queensCount)
{
    NQueensSolver<Board> solver;
    Stopwatch stopwatch;
    std::chrono::duration<double, std::milli> sum = std::chrono::duration<double>::zero();
    std::vector<Board> solution;
    for(std::size_t i = 0; i < COUNT; ++i)
    {
        stopwatch.start();
        solution = solver.solve(queensCount);
        stopwatch.stop();
        sum += stopwatch.duration();
    }
    std::cout << str << ": " << solution.size() << "\n";
    std::cout << "Time spent (" << str << "): " << (sum / static_cast<double>(COUNT)).count() << "\n";
}

int main(int argc, char** argv)
{
    BitBoardTests tests;
    bool result = false;
    try
    {
        result = tests.testAll();
    }
    catch(std::runtime_error& error)
    {
        std::cout << error.what() << "\n";
    }
    if(result)
        std::cout << "All tests passed successfully!\n";

    const std::size_t SIZE = 15;
    const std::size_t COUNT = 10;

    test<ArrayBoardWrapper<SIZE, SIZE>, COUNT>("Array solution", SIZE);
    test<BitBoardWrapper<SIZE, SIZE>, COUNT>("BitBoard solution", SIZE);
    test<BitsetWrapper<SIZE, SIZE>, COUNT>("BitSet solution", SIZE);
}

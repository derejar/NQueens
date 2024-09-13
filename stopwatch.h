#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <stdexcept>
#include <iostream>

template <typename Ratio = std::ratio<1, 1>, typename Clock = std::chrono::high_resolution_clock>
class Stopwatch
{
public:
    void start()
    {
        m_isStarted = true;
        m_startTime = Clock::now();
    }
    void stop()
    {
        if(!m_isStarted)
            throw std::runtime_error("Stopwatch wasnt started!");
        m_isStarted = false;
        typename Clock::time_point endTime = Clock::now();
        m_timeSpended = endTime - m_startTime;
    }
    std::chrono::duration<double, Ratio> duration() const
    {
        if(m_isStarted)
            throw std::runtime_error("Stopwatch is working!");
        return m_timeSpended;
    }
private:
    typename Clock::time_point m_startTime;
    std::chrono::duration<double, Ratio> m_timeSpended;
    bool m_isStarted = false;
};

template <typename Ratio, typename Clock>
std::ostream& operator<<(std::ostream& os, const Stopwatch<Ratio, Clock>& stopwatch)
{
    os << stopwatch.duration().count();
    return os;
}

#endif

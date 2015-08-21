#ifndef ALGO3_TP1_STATISTICS_H
#define ALGO3_TP1_STATISTICS_H

#include <list>
#include <map>
#include <chrono>

class Counter;
class Timer;

/***********************************************************************************************************************
 * Statistics
 **********************************************************************************************************************/
class Statistics {
    friend class Counter;
    friend class Timer;
public:
    static Statistics & getInstance();
    void dump(std::string file);
private:
    void set(std::string name, long long x);
    void reset(std::string name, long long x);

    Statistics();
    Statistics(Statistics const&) = delete;
    void operator=(Statistics const&)  = delete;

    std::map<std::string, std::list<long long>> counters;
};

/***********************************************************************************************************************
 * Counter
 **********************************************************************************************************************/
class Counter {
public:
    Counter(std::string name, long long i);
    std::string inline getName() const;
    operator long long() const;
    Counter & operator+=(const Counter &m);
    Counter & operator-=(const Counter &m);
    Counter & operator++();
    Counter & operator--();
    void set(long long x);
    ~Counter();
private:
    std::string name;
    long long i;
};

/***********************************************************************************************************************
 * Timer
 **********************************************************************************************************************/
class Timer {
public:
    Timer(std::string name);
    std::string inline getName() const;
    void reset(bool write);
    void stop();
    ~Timer();
private:
    std::string name;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    bool stopped;
};

#endif //ALGO3_TP1_STATISTICS_H

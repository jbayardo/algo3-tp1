//
// Created by julian on 8/15/15.
//

#include "Statistics.h"

/***********************************************************************************************************************
 * Statistics
 **********************************************************************************************************************/
Statistics static &Statistics::getInstance() {
    static Statistics instance;
    return instance;
}

void Statistics::dump(std::string file) {
    std::fstream output(file, std::ios_base::out);

    for (auto &it : this->counters) {
        output << it.first << "\t\t\t";

        for (auto &lst : it.second) {
            output << lst << " ";
        }

        output << std::endl;
    }

    output.close();
}

void Statistics::set(std::string name, long long x) {
    try {
        std::list<long long> &temporal(this->counters.at(name));

        temporal.pop_front();
        temporal.push_front(x);
    } catch(...) {
        std::list<long long> empty;
        empty.push_back(x);
        counters.insert(std::pair<std::string, std::list<long long>>(name, empty));
    }
}

void Statistics::reset(std::string name, long long x = 0) {
    try {
        std::list<long long> &temporal(this->counters.at(name));
        temporal.push_front(x);
    } catch(...) {
        std::list<long long> empty;
        empty.push_back(x);
        counters.insert(std::pair<std::string, std::list<long long>>(name, empty));
    }
}

Statistics::Statistics() {}

/***********************************************************************************************************************
 * Counter
 **********************************************************************************************************************/
Counter::Counter(std::string name, long long i = 0) : name(name), i(i) { }

std::string inline Counter::getName() const {
    return this->name;
}

Counter::operator long long() const {
    return this->i;
}

Counter &Counter::operator+=(const Counter &m) {
    this->i += m.i;
    return *this;
}

Counter &Counter::operator-=(const Counter &m) {
    this->i -= m.i;
    return *this;
}

Counter &Counter::operator++() {
    this->i++;
    return *this;
}

Counter &Counter::operator--() {
    this->i++;
    return *this;
}

void Counter::set(long long x) {
    i = x;
}

Counter::~Counter() {
    Statistics::getInstance().reset(this->name, i);
}

/***********************************************************************************************************************
 * Timer
 **********************************************************************************************************************/
Timer::Timer(std::string name)
        : name(name), start(std::chrono::steady_clock::now()), end(std::chrono::steady_clock::now()), stopped(false) { }

std::string inline Timer::getName() const {
    return this->name;
}

void Timer::reset(bool write = false) {
    this->end = std::chrono::steady_clock::now();

    if (write) {
        Statistics::getInstance().reset(this->name, std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start).count());
    }

    this->start = std::chrono::steady_clock::now();
    this->stopped = false;
}

void Timer::stop() {
    if (stopped) {
        throw new std::runtime_error("Tried to stop an already stopped timer.");
    }

    this->stopped = true;
    this->end = std::chrono::steady_clock::now();
    Statistics::getInstance().reset(this->name, std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start).count());
}

Timer::~Timer() {
    if (!stopped) {
        this->end = std::chrono::steady_clock::now();
        Statistics::getInstance().reset(this->name, std::chrono::duration_cast<std::chrono::microseconds>(this->end - this->start).count());
    }
}
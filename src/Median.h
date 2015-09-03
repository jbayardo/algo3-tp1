#ifndef ALGO3_TP1_MEDIANA_H
#define ALGO3_TP1_MEDIANA_H

#include "Statistics.h"
#include <queue>
#include <vector>
#include <functional>
#include <list>

class Median {
public:
    Median();

    template<class Iterator>
    std::list<int> insert(Iterator elements) {
        Timer timer("Median Timer");

        std::list<int> output;

        for (auto &x : elements) {
            this->insertSingle(x);
            output.push_back(this->get());
        }

        return output;
    }

    int get();
private:
    void insertSingle(int x);

    std::priority_queue<int, std::vector<int>> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;
};

#endif //ALGO3_TP1_MEDIANA_H

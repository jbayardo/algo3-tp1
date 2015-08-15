//
// Created by julian on 8/15/15.
//

#ifndef ALGO3_TP1_MEDIANA_H
#define ALGO3_TP1_MEDIANA_H

#include <list>
#include <queue>
#include <vector>

class Median {
public:
    Median();
    std::list<int> insert(const std::list<int> &elements);
    int get();
private:
    void insertSingle(int x);

    std::priority_queue<int, std::vector<int>> left;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right;
};

#endif //ALGO3_TP1_MEDIANA_H

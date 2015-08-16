#ifndef ALGO3_TP1_CAMINO_H
#define ALGO3_TP1_CAMINO_H

#include <tuple>
#include <vector>
#include <iostream>
#include <fstream>

class Path {
public:
    static int greedy(int meters, const std::vector<int> &distances);
};


#endif //ALGO3_TP1_CAMINO_H

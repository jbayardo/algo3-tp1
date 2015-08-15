#ifndef ALGO3_TP1_CAMINO_H
#define ALGO3_TP1_CAMINO_H

#include <tuple>
#include <vector>

class Camino {
public:
    static std::tuple<int, int> greedy(int metros, const std::vector<int> &distancias);
};


#endif //ALGO3_TP1_CAMINO_H

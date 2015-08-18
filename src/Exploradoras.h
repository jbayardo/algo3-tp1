#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <algorithm>
#include <vector>
#include <string>
#include <stdint.h>


class Exploradoras {

public:
    std::pair<int, std::string> backtracking(std::vector<std::pair<char, std::string>> explorers_relations);
    bool next_permutation(std::string perm);

};


#endif //ALGO3_TP1_EXPLORADORAS_H

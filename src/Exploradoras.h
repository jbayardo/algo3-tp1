#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <map>
#include <set>

class Exploradoras {
public:
    Exploradoras(const std::map<char, std::set<char>> &relations);
    std::pair<int, std::string> exhaustive(const std::map<char, std::set<char>> &explorers_relations);
private:
    std::pair<int, int> calculateDistance(const std::string &seats);

    std::map<char, std::set<char>> explorers_relations;
};


#endif //ALGO3_TP1_EXPLORADORAS_H

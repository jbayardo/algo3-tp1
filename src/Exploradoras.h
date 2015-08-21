#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <string>
#include <map>
#include <set>

class Exploradoras {
private:
    std::map<char, std::set<char>> explorers_relations;

	std::pair<int, int> Exploradoras::calculateDistance(const std::string &seats);
public:
	Exploradoras(const std::map<char, std::set<char>> &explorers_relations);
    std::pair<int, std::string> backtracking();
    bool next_permutation(std::string& perm);
};


#endif //ALGO3_TP1_EXPLORADORAS_H

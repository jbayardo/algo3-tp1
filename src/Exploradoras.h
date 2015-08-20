#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <stdint.h>




class Exploradoras {
private:
    std::map<char, std::set<char>> explorers_relations;
public:
	Exploradoras(const std::map<char, std::set<char>> &explorers_relations);
    std::pair<int, std::string> backtracking();
	bool is_friend(char a_explorer, char other);
    bool next_permutation(std::string& perm);
};


#endif //ALGO3_TP1_EXPLORADORAS_H

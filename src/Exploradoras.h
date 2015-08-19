#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdint.h>



class Exploradoras {
private:
    std::unordered_map<char, std::string> explorers_relations;
public:
	Exploradoras(const std::unordered_map<char, std::string> &explorers_relations);
    std::pair<int, std::string> backtracking();
	bool is_friend(char a_explorer, char other);
    bool next_permutation(std::string perm);
};


#endif //ALGO3_TP1_EXPLORADORAS_H

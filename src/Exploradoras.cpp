#include "Exploradoras.h"

Exploradoras::Exploradoras(const std::map<char, std::set<char>>& explorers_relations) {
    this->explorers_relations = explorers_relations;
}


std::pair<int, std::string> Exploradoras::backtracking() {
    std::string explorers(explorers_relations.size(), 0);

    std::size_t i = 0;
    for (auto it = explorers_relations.cbegin(); it != explorers_relations.cend(); it++) {
        explorers[i] = it->first;
        i++;
    }

    int min_distance = -1;
    std::string best_seats;
    auto max_pair = 0;

    do {
        auto current_distance = 0;
        auto max_d_pair = 0;

        for (int e = 0; e < explorers.size(); e++) {
            for (int start = e + 1; start < explorers.size(); ++start) {
                int distance = std::min(start - e, (int)explorers.size() - start + e);
                bool friendship = is_friend(explorers[e], explorers[start]);
                current_distance += distance * 2 * friendship;
                max_d_pair = std::max(max_d_pair, distance);
            }
        }
        if ((current_distance < min_distance) || (min_distance < 0)) {
            min_distance = current_distance;
            best_seats = explorers;
            max_pair = max_d_pair;
        }
    } while (next_permutation(explorers));

    return std::make_pair(max_pair, best_seats);
}

bool Exploradoras::is_friend(char a_explorer, char other)
{
    auto res = explorers_relations.find(a_explorer);

    if (res == explorers_relations.end()) {
        return false;
    }
    auto friends = res->second;
    auto found = friends.find(other);
    return (found != friends.end());
}


#define SWAP(a, b)  {auto temp = a; a = b; b = temp;}

bool Exploradoras::next_permutation(std::string& perm) {

    auto n = (int)perm.size();
    int i = 0;
    bool next_p = false;

    for (; i < n - 1; i++) {
        if (perm[i] < perm[i + 1]) {
            next_p = true;
            break;
        }
    }

    if (!next_p) {
        return false;
    }

    i = n - 1;

    while (perm[i - 1] >= perm[i]) {
        i = i - 1;
    }

    int j = n;

    while (perm[j - 1] <= perm[i - 1]) {
        j = j - 1;
    }

    SWAP(perm[i - 1], perm[j - 1]);

    i++;
    j = n;

    while (i < j) {
        SWAP(perm[i - 1], perm[j - 1]);
        i++;
        j--;
    }

    return true;
}



/*
COMPLEJIDAD TOTAL:
e! . (e . e . a  + e) = e!. e2.a + e
*/


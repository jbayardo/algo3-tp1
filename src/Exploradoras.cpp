#include "Exploradoras.h"

Exploradoras::Exploradoras(const std::unordered_map<char, std::string>& explorers_relations) {
    this->explorers_relations = explorers_relations;
}


std::pair<int, std::string> Exploradoras::backtracking() {
    unsigned int letters = 26;

    std::vector<std::vector<bool>> friendship_table(letters, std::vector<bool>(letters, false));
    std::string explorers(explorers_relations.size(), 0); 

    std::size_t i = 0;
    for (auto it = explorers_relations.cbegin(); it != explorers_relations.cend(); it++) {
        explorers[i] = it->first;
        i++;
    }

    std::sort(explorers.begin(), explorers.end());

    auto min_distance = INTMAX_MAX;
    std::string best_seats;

    do {

        for (int e = 0; e < explorers.size(); e++) {
            unsigned int current_distance = 0;

            for (int start = e + 1; start < explorers.size(); ++start) {
                bool friendship_status = is_friend(explorers[e], explorers[start]);
                current_distance = std::min(start, ((int)explorers.size()) - start) * friendship_status;
            }

            if (current_distance < min_distance) {
                min_distance = current_distance;
                best_seats = explorers;
            }
        }
    } while (next_permutation(explorers));

    return std::make_pair(min_distance, best_seats);
}

bool Exploradoras::is_friend(char a_explorer, char other)
{
    auto res = explorers_relations.find(a_explorer);

    if (res == explorers_relations.end()) {
        return false;
    }
    std::string& friends = res->second;
    std::size_t found = friends.find(other);
    return (found != std::string::npos);
}


#define SWAP(a, b)  {auto temp = a; a = b; b = temp;}

bool Exploradoras::next_permutation(std::string perm) {

    auto n = (int)perm.size();
    auto i = 0;
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

    for (; perm[i - 1] >= perm[i]; i--);
    auto j = n;

    for (; perm[j - 1] >= perm[i - 1]; j--);

    SWAP(perm[i - 1], perm[j - 1]);

    i++;
    j = n;

    for (; i < j; i++, j--) {
        SWAP(perm[i - 1], perm[j - 1]);
    }
    return next_p;
}



/*
COMPLEJIDAD TOTAL:
e! . (e . e . a  + e) = e!. e2.a + e
*/


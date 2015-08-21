#include "Exploradoras.h"
#include <algorithm>
#include <limits>

Exploradoras::Exploradoras(const std::map<char, std::set<char>>& explorers_relations) {
    this->explorers_relations = explorers_relations;
}

std::pair<int, int> Exploradoras::calculateDistance(const std::string &seats) {
	int sumDistance = 0;
	int maxDistance = -2;

	// TODO: verificar que no estemos incluyendo una distancia mas de una vez.
	for (auto &it : this->explorers_relations) {
		std::size_t position = seats.find_first_of(it.first);

		for (const char &friends : it.second) {
			std::size_t friendPosition = seats.find_first_of(friends);

			int distance = std::min(
				std::abs(static_cast<int>(position) - static_cast<int>(friendPosition)),
				std::abs(static_cast<int>(position) + static_cast<int>(seats.length()) - static_cast<int>(friendPosition)));

			distance = std::min(
				distance,
				std::abs(static_cast<int>(friendPosition) + static_cast<int>(seats.length()) - static_cast<int>(position)));

			sumDistance += distance;

			if (distance > maxDistance) {
				maxDistance = distance;
			}
		}
	}

	return std::make_pair(sumDistance, maxDistance);
}

std::pair<int, std::string> Exploradoras::backtracking() {
	// ASSERT: la cantidad de exploradoras es mayor a 0
	std::string exploradores;

	for (auto &it : this->explorers_relations) {
		exploradores += it.first;
	}

	std::sort(exploradores.begin(), exploradores.end());

	std::string bestSeats;
	int maxDistance = -1;
	int minSum = std::numeric_limits<int>().max();  // infinito
	bool hasSolution = false;

	do {
		std::pair<int, int> distances = this->calculateDistance(exploradores);

		if (distances.first <= minSum) {
			if (hasSolution) {
				if (distances.second <= maxDistance) {
					bestSeats = exploradores;
					maxDistance = distances.second;
					minSum = distances.first;
				}
			} else {
				bestSeats = exploradores;
				maxDistance = distances.second;
				minSum = distances.first;
				hasSolution = true;
			}
		}
	} while (next_permutation(exploradores));

	return std::make_pair(maxDistance, bestSeats);
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


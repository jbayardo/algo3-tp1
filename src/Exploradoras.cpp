#include "Statistics.h"
#include "Exploradoras.h"
#include <algorithm>

#define SWAP(a, b)  {auto temp = a; a = b; b = temp;}

bool next_permutation(std::string &perm) {
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

Exploradoras::Exploradoras(const std::map<char, std::set<char>> &relations)
        : explorers_relations(relations) { };

std::pair<int, int> Exploradoras::calculateDistance(const std::string &seats) {
    int sumDistance = 0;
    int maxDistance = -1;

    for (auto &it : explorers_relations) {
        std::size_t position = seats.find_first_of(it.first);

        for (auto &friends : it.second) {
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

std::pair<int, std::string> Exploradoras::exhaustive(const std::map<char, std::set<char>> &explorers_relations) {
    Timer timer("Exploradoras Exhaustive Search Timer");
	// ASSERT: la cantidad de exploradoras es mayor a 0
	std::string exploradores;

	for (auto &it : explorers_relations) {
		exploradores += it.first;
	}

	std::sort(exploradores.begin(), exploradores.end());

	std::string bestSeats;
	int maxDistance = -1;
	int minSum = std::numeric_limits<int>().max();
	bool hasSolution = false;

	do {
		auto distances = calculateDistance(exploradores);

        if (distances.first < minSum || !hasSolution) {
            bestSeats = exploradores;
            maxDistance = distances.second;
            minSum = distances.first;
            hasSolution = true;
        }
	} while (next_permutation(exploradores));

	return std::make_pair(maxDistance, bestSeats);
}

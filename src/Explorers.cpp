#include "Statistics.h"
#include "Explorers.h"
#include <algorithm>
#include <bits/stl_queue.h>

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

Explorers::Explorers(const std::map<char, std::set<char>> &relations)
        : relations(relations) { };

std::pair<int, int> Explorers::calculateDistance(const std::string &seats) {
    int sumDistance = 0;
    int maxDistance = -1;

    for (auto &it : relations) {
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

std::pair<int, std::string> Explorers::exhaustive() {
    Timer timer("Explorers Exhaustive Search Timer");
	// ASSERT: la cantidad de exploradoras es mayor a 0
	std::string exploradores;

	for (auto &it : relations) {
		exploradores += it.first;
	}

	std::sort(exploradores.begin(), exploradores.end());

	std::string bestSeats;
	int maxDistance = -1;
	int minSum = std::numeric_limits<int>().max();
	bool hasSolution = false;

	do {
		auto distances = calculateDistance(exploradores);

        if (distances.first <= minSum && (hasSolution && (distances.second < maxDistance || (distances.second == maxDistance && exploradores < bestSeats)) || !hasSolution))
        {
            bestSeats = exploradores;
            maxDistance = distances.second;
            minSum = distances.first;
            hasSolution = true;
        }
	} while (next_permutation(exploradores));

	return std::make_pair(maxDistance, bestSeats);
}

Bracelet Explorers::backtracking(BraceletFilter &keep) {
    Timer timer("Explorers Backtracking Search Timer");
    std::priority_queue<Bracelet> processing;
    Bracelet initial(this->relations);

    // El primer elemento a procesar es el brazalete con el menor elemento lexicografico unicamente
    initial.insert(initial.missing(), 0);
    processing.push(initial);

    while (!processing.empty()) {
        // Obtenemos el brazalete de menor suma, menor distancia entre pares, y menor orden lexicográfico.
        Bracelet current = processing.top();
        processing.pop();

        // Si tenemos la solución del problema, devolvemos eso.
        if (current.complete() && initial < current) {
            initial = current;
        }

        // Si no, tomamos alguno de los que falte, y generamos todas las formas de insertarlo.
        char explorer = current.missing();

        // Probamos hasta el - 1 porque agregar al final es lo mismo que agregar al principio.
        for (std::size_t i = 0; i < current.size() - 1; ++i) {
            Bracelet generated(current);
            generated.insert(explorer, i);

            // Borramos las partes del árbol que no nos sirvan.
            if (keep(generated)) {
                processing.push(generated);
            }
        }
    }

    // TODO:
    return initial;
}
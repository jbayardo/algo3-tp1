#include "Statistics.h"
#include "Explorers.h"
#include <stack>
#include <algorithm>

Explorers::Explorers(const std::map<char, std::set<char>> &relations)
        : relations(relations) { };

/******************************************************************************
 * Solución por fuerza bruta
 *****************************************************************************/
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

/******************************************************************************
 * Solución por backtracking
 *****************************************************************************/
Bracelet::Bracelet(const std::map<char, std::set<char>> &relations) : relations(relations), sum(0), distance(0) {

    // Inicializamos el arreglo con todos los nombres de exploradoras, en orden lexicografico inverso
    for (auto relation = this->relations.crbegin(); relation != this->relations.crend(); ++relation) {
        this->left.push_back(relation->first);
    }
}

Bracelet::Bracelet(const Bracelet &c)
        : relations(c.relations), bracelet(c.bracelet), left(c.left), sum(c.sum), distance(c.distance) { }

std::size_t inline Bracelet::size() const {
    return this->bracelet.length();
}

void Bracelet::insert(char c, std::size_t index) {
    // ASSERT: index < size, index >= 0

    this->bracelet.insert(this->bracelet.begin() + index, c);
    this->distance = 0;
    this->sum = 0;

    // Recorremos las entradas del mapa
    for (auto &iterator : this->relations) {
        std::size_t position = this->bracelet.find_first_of(iterator.first);

        // El elemento podría no estar todavía en el bracelet!
        if (position != std::string::npos) {
            // Recorremos los amigos, y calculamos los datos necesarios para el problema
            for (auto &friends : iterator.second) {
                std::size_t friendPosition = this->bracelet.find_first_of(friends);

                // Las relaciones del elemento podrían no estar todavía en el bracelet!
                if (friendPosition != std::string::npos) {
                    std::size_t friendDistance = std::min(
                            abs_diff(position, friendPosition),
                            abs_diff(position + this->bracelet.length(), friendPosition));

                    friendDistance = std::min(
                            friendDistance,
                            abs_diff(friendPosition + this->bracelet.length(), position));

                    this->sum += friendDistance;

                    if (friendDistance > this->distance) {
                        this->distance = friendDistance;
                    }
                }
            }
        }
    }

}

Bracelet &Bracelet::operator=(const Bracelet &r) {
    // Si no estamos asignandonos a nosotros mismos
    if (this != &r) {
        // No podemos asignar un bracelet con otro que no se trate de las mismas relaciones
        // Más todavía, debe ser el mismo objeto en memoria.
        if (&this->relations != &r.relations) {
            throw std::runtime_error("Bracelets must be bound to the same relationship graph");
        }

        this->bracelet = r.bracelet;
        this->left = r.left;
        this->sum = r.sum;
        this->distance = r.distance;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Bracelet &bracelet) {
    std::stringstream output;
    output << bracelet.distance << " " << bracelet.bracelet;
    stream << output.str();
    return stream;
}

bool Bracelet::operator<(const Bracelet &r) const {
    if (this->size() < r.size()) {
        return true;
    }

    if (this->size() > r.size()) {
        return false;
    }

    if (this->sum > r.sum) {
        // Tamaños iguales, suma mayor
        return true;
    } else if (this->sum == r.sum) {
        // Tamaños iguales, sumas iguales
        if (this->distance > r.distance) {
            // Tamaños iguales, sumas iguales, mayor distancia
            return true;
        } else if (this->distance == r.distance) {
            // Tamaños iguales, sumas iguales, distancias iguales

            if (this->bracelet < r.bracelet) {
                return false;
            } else if (this->bracelet != r.bracelet) {
                return true;
            }

            return false;
        } else {
            // Tamaños iguales, sumas iguales, menor distancia
            return false;
        }
    } else {
        // Tamaños iguales, suma menor
        return false;
    }
}

inline bool Bracelet::complete() const {
    return this->left.length() == 0;
}

char Bracelet::missing() {
    if (this->left.length() > 0) {
        char r = this->left.back();
        this->left.pop_back();
        return r;
    } else {
        throw std::out_of_range("No more missing characters");
    }
}

std::size_t Bracelet::getDistance() const {
    return this->distance;
}

std::size_t Bracelet::getSum() const {
    return this->sum;
}

Bracelet Explorers::backtracking(BraceletFilter keep) {
    Timer timer("Explorers Backtracking Search Timer");
    std::stack<Bracelet> processing;
    Bracelet initial(this->relations);

    // El primer elemento a procesar es el brazalete con el menor elemento lexicografico unicamente
    initial.insert(initial.missing(), 0);
    processing.push(initial);

    // Tomamos como referencia para la purga a un brazalete completo cualquiera.
    while (!initial.complete()) {
        initial.insert(initial.missing(), 0);
    }

    // Hacemos que el filtro sepa que existe esta solución completa, así podemos purgar desde el comienzo
    keep(initial);

    while (!processing.empty()) {
        // Obtenemos el brazalete de menor suma, menor distancia entre pares, y menor orden lexicográfico.
        Bracelet current = processing.top();
        processing.pop();

        if (current.complete()) {
            // Si tenemos la solución del problema, nos fijamos si es la mejor!.
            if (initial < current) {
                initial = current;
            }
        } else {
            // Si no, tomamos alguno de los que falte, y generamos todas las formas de insertarlo.
            char explorer = current.missing();

            // Empezamos insertando al final (que es el menor elemento lexicografico) y vamos hasta el casi primer caso,
            // ya que insertar en la posición 0 es lo mismo que insertar al final.
            for (std::size_t i = current.size(); i >= 1; --i) {
                Bracelet generated(current);
                generated.insert(explorer, i);

                // Borramos las partes del árbol que no nos sirvan.
                if (keep(generated)) {
                    processing.push(generated);
                }
            }
        }
    }

    return initial;
}
#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#ifdef _NOEXCEPT
#define noexcept _NOEXCEPT
#endif

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

template<typename T>
inline T abs_diff(T a, T b) {
    return a > b ? a - b : b - a;
}

class Bracelet {
public:
    Bracelet(const std::map<char, std::set<char>> &relations)
        : relations(relations), sum(0), distance(0) {

        // Inicializamos el arreglo con todos los nombres de exploradoras, en orden lexicografico inverso
        for (auto relation = this->relations.crbegin(); relation != this->relations.crend(); ++relation) {
            this->left.push_back(relation->first);
        }
    }

    Bracelet(const Bracelet &c)
        : relations(c.relations), bracelet(c.bracelet), left(c.left), sum(c.sum), distance(c.distance)
    { }

    /*! Devuelve la cantidad de exploradoras presentes en el bracelet
     */
    inline std::size_t size() const noexcept {
        return this->bracelet.length();
    }

    /*! Inserta una exploradora en el bracelet. El indice se mide desde el nodo inicial.
     */
    // TODO: ver si es noexcept
    void insert(char c, std::size_t index) {
        // ASSERT: index < size, index >= 0

#ifdef EJ3_FAST_INSERTION
        // TODO:
        throw std::runtime_error("Not implemented yet");
#else
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
#endif
    }

    Bracelet &operator=(const Bracelet &r) throw(std::runtime_error) {
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

    // TODO: ver si es noexcept
    friend std::ostream &operator<<(std::ostream &stream, const Bracelet &bracelet) {
        std::stringstream output;
        output << bracelet.distance << " " << bracelet.bracelet;
        stream << output.str();
        return stream;
    }

    /*! Compara dos bracelets
     */
    bool operator<(const Bracelet &r) const noexcept {
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

    /*! Devuelve true cuando el bracelet está completo y no hay nada más que agregar
     */
    inline bool complete() const noexcept {
        return this->left.length() == 0;
    }

    /*! Devuelve una exploradora que falte insertar en el bracelet para ser completo. Además, de todas las que falten,
     * siempre es la menor lexicograficamente
     */
    char missing() throw(std::out_of_range) {
        if (this->left.length() > 0) {
            char r = this->left.back();
            this->left.pop_back();
            return r;
        } else {
            throw std::out_of_range("No more missing characters");
        }
    }

	std::size_t MaxDistance() const { return this->distance; }
	std::size_t RelationsSum() const { return this->sum; }

    virtual ~Bracelet() { }
private:
    /*! Mapa de relaciones entre las exploradoras. Asumimos que hay una entrada por cada exploradora que deba estar en
     * la ronda final
     */
    const std::map<char, std::set<char>> &relations;

    /*! Guarda el bracelet actual, es decir, las exploradoras que estan en la ronda
     */
    std::string bracelet;

    /*! Las que faltan, en orden lexicografico inverso.
     */
    std::string left;

    /*! Suma de las distancias entre amistades
     */
    std::size_t sum;

    /*! Distancia maxima entre amistades
     */
    std::size_t distance;
};

// Cuanta menor complejidad sea posible, mejor.
class BraceletFilter {
public:
	BraceletFilter() : sum(std::numeric_limits<int>().max()), distance(std::numeric_limits<int>().max()) {}
    /*! Si devuelve true, se guarda el bracelet, si no, se purga. Por defecto no realizamos purga.
     */
    virtual bool operator()(const Bracelet &b) { 
		if (b.RelationsSum() > this->sum) {
			return false;
		} else if (b.RelationsSum() == this->sum) {
			if (b.MaxDistance() > this->distance) {
				return false;
			} else if (b.MaxDistance() < this->distance) {
				if (b.complete()) {
					this->sum = b.RelationsSum();
					this->distance = b.MaxDistance();
				}
				return true;
			} else {
				return true;
			}
		} else {
			if (b.complete()) {
				this->sum = b.RelationsSum();
				this->distance = b.MaxDistance();
			}
			return true;
		}
	}
private:
	std::size_t sum;
	std::size_t distance;
};

class Explorers {
public:
    Explorers(const std::map<char, std::set<char>> &);
    std::pair<int, std::string> exhaustive();
    Bracelet backtracking(BraceletFilter &);
private:
    std::pair<int, int> calculateDistance(const std::string &seats);

    std::map<char, std::set<char>> relations;
};


#endif //ALGO3_TP1_EXPLORADORAS_H

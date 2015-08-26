#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <map>
#include <set>
#include <bitset>
#include <string>

class Bracelet {
public:
    Bracelet(const std::map<char, std::set<char>> &relations)
        : relations(relations), sum(0), distance(0) {

        // Inicializamos el arreglo con todas las relaciones posibles
        for (auto &relation : this->relations) {
            this->left.push_back(relation.first);
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
    void insert(char c, std::size_t index) {
        // ASSERT: index < size, index >= 0
        // Avanzamos hasta que index sea 0 (o sea, hasta que no haya que movernos más)
        for (auto it = this->bracelet.begin(); it != this->bracelet.end(); ++it, --index) {
            if (index == 0) {
                // Insertamos en esta posición el caracter que falta
                this->bracelet.insert(it, c);
                it++;
            } else {
                // Aca vamos a caer siempre que estemos antes o despues de donde hay que insertar
                // el abs de index nos dice a que distancia estamos de donde insertamos al nuevo caracter
                // TODO: actualizar las sumas.
                it++;
            }
        }
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

    /*! Compara dos bracelets
     */
    bool operator<(const Bracelet &r) const noexcept {
        if (this->size() < r.size()) {
            return true;
        }

        if (this->sum < r.sum) {
            return true;
        }

        if (this->sum == r.sum) {
            if (this->distance < r.distance) {
                return true;
            }

            // TODO: aca hay un problema con los ordenes lexicograficos.
            if (this->distance == r.distance && this->bracelet < r.bracelet) {
                return true;
            }
        }

        return false;
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
    /*! Si devuelve true, se guarda el bracelet, si no, se purga.
     */
    virtual bool operator()(const Bracelet &) { return true; }
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

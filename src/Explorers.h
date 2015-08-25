#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <map>
#include <set>
#include <bitset>
#include <string>

class Bracelet {
public:
    Bracelet(const std::map<char, std::set<char>> &relations)
        : relations(relations)
    { }

    // TODO: crear comparador, el de arriba de todo tiene que ser el de menor suma, menor distancia.
    // TODO: además, al imprimirse debe hacerlo de la forma que le de el menor orden lexicografico posible.
    Bracelet(const Bracelet &c)
        : relations(c.relations), left(c.left), bracelet(c.bracelet)
    { }

    Bracelet(Bracelet &&c)
        : relations(relations) {

    }

    /*! Devuelve la cantidad de exploradoras presentes en el bracelet
     */
    inline std::size_t size() const noexcept {
        return this->bracelet.length();
    }

    /*! Inserta una exploradora en el bracelet
     */
    void insert(char c, std::size_t index) {
        this->bracelet.insert(this->bracelet.begin() + index, c);
    }

    /*! Compara dos bracelets
     */
    friend bool operator<(const Bracelet &b1, const Bracelet &b2) const noexcept {
        if (b1.size() < b2.size()) {
            return true;
        }

        if (b1.sum < b2.sum) {
            return true;
        }

        if (b1.sum == b2.sum) {
            if (b1.distance < b2.distance) {
                return true;
            }

            // TODO: aca hay un problema con los ordenes lexicograficos.
            if (b1.distance == b2.distance && b1.bracelet < b2.bracelet) {
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

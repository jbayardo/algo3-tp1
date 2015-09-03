#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#ifdef _NOEXCEPT
#define noexcept _NOEXCEPT
#endif

#include <map>
#include <set>
#include <string>
#include <sstream>

template<typename T>
inline T abs_diff(T a, T b) {
    return a > b ? a - b : b - a;
}

class Bracelet {
public:
    /*! Constructor por defecto, cabe destacar que cada bracelet está asociado
     * a un único grafo de relaciones.
     */
    Bracelet(const std::map<char, std::set<char>> &relations);

    /*! Constructor por copia
     */
    Bracelet(const Bracelet &c);

    /*! Devuelve la cantidad de exploradoras presentes en el bracelet
     */
    std::size_t inline size() const;

    /*! Inserta una exploradora en el bracelet. El indice se mide desde el nodo inicial.
     */
    void insert(char c, std::size_t index);

    /*! Asigna un bracelet a otro
     */
    Bracelet & operator=(const Bracelet &r);

    /*! Imprime un bracelet
     */
    friend std::ostream & operator<<(std::ostream &stream, const Bracelet &bracelet);

    /*! Compara dos bracelets
     */
    bool operator<(const Bracelet &r) const;

    /*! Devuelve true cuando el bracelet está completo y no hay nada más que agregar
     */
    inline bool complete() const {
        return this->left.length() == 0;
    }

    /*! Devuelve una exploradora que falte insertar en el bracelet para ser completo. Además, de todas las que falten,
     * siempre es la menor lexicograficamente
     */
    inline char missing() const {
        if (this->left.length() > 0) {
            return this->left.back();
        } else {
            throw std::out_of_range("No more missing characters");
        }
    }

    /*! Devuelve la maxima distancia entre dos amistades
     */
    inline std::size_t getDistance() const {
        return this->distance;
    }

    /*! Devuelve la suma de las distancias entre todas las amistades
     */
    inline std::size_t getSum() const {
        return this->sum;
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

class BraceletFilter {
public:
    /*! Si devuelve true, se guarda el bracelet, si no, se purga. Por defecto no realizamos purga.
     */
    virtual bool operator()(const Bracelet &b) noexcept {
        return true;
	}
};

class PruningFilter : public BraceletFilter {
public:
    PruningFilter()
            : sum(std::numeric_limits<std::size_t>().max()), distance(std::numeric_limits<std::size_t>().max())
    { }

    bool operator()(const Bracelet &b) noexcept {
        if (b.getSum() > this->sum) {
            return false;
        } else {
            if (b.complete()) {
                this->sum = b.getSum();
                this->distance = b.getDistance();
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
    /*! Constructor de una instancia del problema
     */
    Explorers(const std::map<char, std::set<char>> &relations);

    /*! Resolución utilizando el algoritmo de backtracking
     */
    Bracelet backtracking(BraceletFilter keep);
private:
    /*! Mapa de relaciones. Guarda las exploradoras que hay que distribuir, y quiénes son sus amigas
     */
    std::map<char, std::set<char>> relations;
};


#endif //ALGO3_TP1_EXPLORADORAS_H

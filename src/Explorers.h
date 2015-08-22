#ifndef ALGO3_TP1_EXPLORADORAS_H
#define ALGO3_TP1_EXPLORADORAS_H

#include <map>
#include <set>
#include <iterator>

class Bracelet {
public:
    Bracelet()
            : sz(0)
    { }

    Bracelet(const Bracelet &c) { }

    inline std::size_t size() const { return this->sz; }

    void insert(char c, std::size_t index) {

    }

    // Tiene que ser O(1)
    bool complete(const std::map<char, std::set<char>> &relations) const {
        return comp;
    }

    // Tiene que ser O(1)
    char missing(const std::map<char, std::set<char>> &relations) const {
        // TODO: verificar si no tenemos que generar esto ordenado
        return 'c';
    }

    virtual ~Bracelet() { }
private:
    bool comp;
    std::size_t sz;
};

// Cuanta menor complejidad sea posible, mejor.
class BraceletFilter {
public:
    virtual bool operator()(const Bracelet &) { }
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

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

    bool complete(const std::map<char, std::set<char>> &relations) const {
        for (auto &relation : relations) {
            if (!relation.first) {
                return false;
            }
        }

        return true;
    }

    std::string missing(const std::map<char, std::set<char>> &relations) const {
        // TODO: verificar si no tenemos que generar esto ordenado
        std::string output;

        for (auto &relation : relations) {
            if (!relation.first) {
                output += relation.first;
            }
        }

        return output;
    }

    virtual ~Bracelet() { }
private:
    std::size_t sz;
};

class Explorers {
public:
    Explorers(const std::map<char, std::set<char>> &relations);
    std::pair<int, std::string> exhaustive();
    Bracelet backtracking();
private:
    std::pair<int, int> calculateDistance(const std::string &seats);

    std::map<char, std::set<char>> relations;
};


#endif //ALGO3_TP1_EXPLORADORAS_H

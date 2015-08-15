#include "Camino.h"
#include "Statistics.h"

int Camino::greedy(int metros, const std::vector<int> &distancias) {
    Timer timer("Path Timer");

    int i = 0; // Comienzo del mejor camino
    int j = 0; // Fin del mejor camino
    int k = 0; // Comienzo del camino actual

    for (int m = 0; m < distancias.size(); ++m) {
        if (distancias[m] - distancias[k] > metros) {
            // Borro cualquier cantidad de greedy que sean necesarias para poder continuar buscando.
            while (distancias[m] - distancias[k] > metros && k < m) {
                ++k;
            }

        }

        // Encontramos un mejor camino, extendiendo el que ya teniamos

        // Si este camino es mejor que el que ya teniamos, lo guardamos.
        if ((m - k) > (j - i)) {
            i = k;
            j = m;
        }
    }

    int output = 0;

    if (i != j) {
        output = j - i + 1;
    }

    return output;
}
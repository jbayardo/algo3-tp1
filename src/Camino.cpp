#include "Camino.h"

std::tuple<int, int> Camino::greedy(int metros, const std::vector<int> &distancias) {
    int i = 0; // Comienzo del mejor camino
    int j = 0; // Fin del mejor camino

    int k = 0; // Comienzo del camino actual

    for (int m = 0; m < distancias.size(); ++m) {
        if (distancias[m] - distancias[k] > metros) {
            // Terminamos con este camino, porque no podemos agregar mas ciudades.

            if ((m - k) >= (j - i)) {
                // Si este camino es mejor que el que ya teniamos, lo guardamos.
                i = k;
                j = m;
            }

            // Borro cualquier cantidad de greedy que sean necesarias para poder continuar buscando.
            while (k < m && distancias[m] - distancias[k] > metros) {
                ++k;
            }

        } else {
            // Encontramos un mejor camino, extendiendo el que ya teniamos
            i = k;
            j = m;
        }
    }

    return std::make_pair(i, j);
}
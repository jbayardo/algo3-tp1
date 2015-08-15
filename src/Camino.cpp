#include "Camino.h"

std::tuple<int, int> Camino::greedy(int metros, const std::vector<int> &distancias) {
    int best_start = 0; // Comienzo del mejor camino
    int best_end = 0; // Fin del mejor camino

    int start = 0; // Comienzo del camino actual

    for (int end = 0; end < distancias.size(); ++end) {
        if (distancias[end] - distancias[start] > metros) {
            // Terminamos con este camino, porque no podemos agregar mas ciudades.

            if ((end - start) >= (best_end - best_start)) {
                // Si este camino es mejor que el que ya teniamos, lo guardamos.
                best_start = start;
                best_end = end;
            }

            // Borro cualquier cantidad de greedy que sean necesarias para poder continuar buscando.
            while (start < end && distancias[end] - distancias[start] > metros) {
                ++start;
            }

        } else {
            // Encontramos un mejor camino, extendiendo el que ya teniamos
            best_start = start;
            best_end = end;
        }
    }

    return std::make_pair(best_start, best_end);
}
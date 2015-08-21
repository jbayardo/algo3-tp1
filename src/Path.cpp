#include "Statistics.h"
#include "Path.h"

int Path::greedy(int meters, const std::vector<int> &distances) {
    Timer timer("Path Timer");

    int bestStart = 0; // Comienzo del mejor camino
    int bestEnd = 0; // Fin del mejor camino
    int start = 0; // Comienzo del camino actual

    for (int end = 0; end < distances.size(); ++end) {
        if (distances[end] - distances[start] > meters) {
            // Borro cualquier cantidad de greedy que sean necesarias para poder continuar buscando.
            while (distances[end] - distances[start] > meters && start < end) {
                ++start;
            }

        }

        // Si este camino es mejor que el que ya teniamos, lo guardamos.
        if ((end - start) > (bestEnd - bestStart)) {
            bestStart = start;
            bestEnd = end;
        }
    }

    // Conectamos alguna ciudad solo cuando los indices son distintos.
    int output = 0;

    if (bestStart != bestEnd) {
        output = bestEnd - bestStart + 1;
    }

    return output;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "Path.h"
#include "Median.h"
#include "Explorers.h"
#include "Statistics.h"

/**
 * Si recibimos la variable runs, se va a correr runs veces seguidas por caso de
 * test. La única vez que se va a imprimir es la última. Esto quiere decir, el
 * archivo de estadísticas va a contener runs veces las mediciones para cada test,
 * uno atrás del otro.
 *
 * Por ejemplo, si tenemos runs=2, con 2 casos de test, los primeros 2 valores del
 * medidor se van a corresponder con el primer caso, y los últimos 2 con el segundo
 * caso.
 */
int main(int argc, char *argv[]) {
    using namespace std;

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " problem{1, 2, 3} input output [runs]{>0}" << endl;
        return 0;
    }

    ifstream input;
    input.open(argv[2], ifstream::in);

    if (!input.is_open()) {
        cout << "Input file not found" << endl;

        input.close();
        return -1;
    }

    ofstream output;
    output.open(argv[3], ofstream::out);

    if (!output.is_open()) {
        cout << "Output file not found" << endl;

        input.close();
        output.close();
        return -1;
    }

    switch (atoi(argv[1])) {
        case 1:
        {
            while (!input.eof()) {
                // Leemos los datos del caso de test actual
                int metros;
                vector<int> cities;

                input >> metros;
                input.ignore();

                // Esto es para que la capital sea considerada
                cities.push_back(0);

				while (input.peek() != char_traits<char>::to_int_type('\n') && input.peek() != char_traits<char>::to_int_type('\n') && !input.eof()) {
                    int km;
                    input >> km;
                    cities.push_back(km);
                }

                // Corremos el algoritmo la cantidad de veces que sea indicada por runs
                if (argc >= 5) {
                    for (int i = 0; i < atoi(argv[4]) - 1; ++i) {
                        Path::greedy(metros, cities);
                    }
                }

                // Corrida final
                output << Path::greedy(metros, cities) << endl;
            }
            break;
        }
        case 2:
        {
			string line;

			while (getline(input, line)) {
                // Leemos los datos del caso de test actual
                list<int> numbers;
				istringstream stream(line);
				string number;

				while (getline(stream, number, ' ')) {
                    numbers.push_back(stoi(number));
                }

                // Corremos el algoritmo la cantidad de veces que sea indicada por runs
                if (argc >= 5) {
                    for (int i = 0; i < atoi(argv[4]) - 1; ++i) {
                        Median temporal;
                        temporal.insert(numbers);
                    }
                }

                // Corrida final
                Median run;
                for (auto &it : run.insert(numbers)) {
                    output << it << ' ';
                }

                output << endl;
            }
            break;
        }
        case 3:
        {
            string line;

            while (getline(input, line)) {
                // Leemos los datos del caso de test actual
                map<char, set<char>> exploradoras;
                istringstream stream(line);
                string data;

                while (getline(stream, data, ';')) {
                    char exploradora = data.front();
                    data.erase(0, 2);
					
					exploradoras[exploradora].insert(data.begin(), data.end());

                    for (size_t i = 0; i < data.length(); i++) {
                        char c = data[i];

                        if (exploradoras.find(c) == exploradoras.end()) {
                            exploradoras[data[i]] = set<char>();
                        }

                        exploradoras[data[i]].insert(exploradora);
                    }
                }

                // Corremos el algoritmo la cantidad de veces que sea indicada por runs
                if (argc >= 5) {
                    for (int i = 0; i < atoi(argv[4]) - 1; ++i) {
                        Explorers temporal(exploradoras);
                        PruningFilter filter;
                        temporal.backtracking(filter);
                    }
                }

                // Corrida final
                Explorers run(exploradoras);
                PruningFilter filter;
                Bracelet res = run.backtracking(filter);
                output << res << endl;
            }
            break;
        }
        default:
            cout << "Usage: " << argv[0] << " problem input output" << endl;
            break;
    }

    input.close();
    output.close();

    std::string path = std::string(argv[3]);
    std::size_t dot = path.find_last_of('.');
    std::string name = path.substr(0, dot);

    Statistics::getInstance().dump(name + ".sts");

    return 0;
}
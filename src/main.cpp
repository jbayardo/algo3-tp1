#include <iostream>
#include <fstream>
#include "Path.h"
#include "Median.h"
#include "Exploradoras.h"
#include <tuple>
#include <sstream>


using namespace std;

int main(int argc, char * argvs[]) {
    if (argc != 4) {
        cout << "usage: " << argvs[0] << " numeroDeEjercicio, archivoEntrada, archivoSalida" << endl;
        return 0;
    }

    ifstream input;
    input.open(argvs[2], ifstream::in);
    ofstream output;
    output.open(argvs[3], ofstream::out);

    if (!input.is_open()) {
        cout << "File not found" << endl;
        return 0;
    }

    switch (atoi(argvs[1])) {
        case 1:
        {
            while (!input.eof()) {
                int metros;
                vector<int> cities;

                input >> metros;
                input.ignore();
                cities.push_back(0);

                while (input.peek() != std::char_traits<char>::to_int_type('\r') && !input.eof()) {
                    int km;
                    input >> km;
                    cities.push_back(km);
                }

                int res = Path::greedy(metros, cities);
                output << res << endl;
            }
            break;
        }
        case 2:
        {
			string line;
			while (getline(input, line)) {
                Median ej2;
                list<int> numbers;
				istringstream line(line);
				string number;
				while (getline(line, number, ' ')) {
                    numbers.push_back(stoi(number));
                }

                list<int> res = ej2.insert(numbers);
                for (auto it : res) {
                    output << it << " ";	//Ver si no jode el ultimo espacio
                }
                output << endl;
            }
            break;
        }
        case 3:
        {
            string line;
            while (getline(input, line)) {
                map<char, set<char>> exploradoras;
                istringstream line(line);
                string data;
                while (getline(line, data, ';')) {
                    char exploradora = data.front();
                    data.erase(0, 2);
                    set<char> friendship(data.begin(), data.end());
                    exploradoras[exploradora] = friendship;
                    for (size_t i = 0; i < data.length(); i++) {
                        char c = data[i];
                        if (exploradoras.find(c) == exploradoras.end()) {
                            exploradoras[data[i]] = set<char>();
                        } 
                        exploradoras[data[i]].insert(exploradora);
                    }
                }
                Exploradoras ej3(exploradoras);
                pair<int, string> res = ej3.backtracking();
                output << res.first <<" "<< res.second << endl;
            }
            break;
        }
        default:
            cout << "usage: " << argvs[0] << " numeroDeEjercicio(1, 2, 3)" << endl;
            break;
    }
    return 0;
}
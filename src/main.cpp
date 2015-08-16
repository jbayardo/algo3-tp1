#include <iostream>
#include <fstream>
#include "Path.h"
#include "Median.h"
#include "Exploradoras.h"
#include <tuple>


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
		case 1: {
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
		} case 2: {
			Median ej2;

			break;
		} case 3: {
			Exploradoras ej3;

			break;
		} default:
			cout << "usage: " << argvs[0] << " numeroDeEjercicio(1, 2, 3)" << endl;
			break;
	}
    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "Path.h"
#include "Median.h"
#include "Explorers.h"
#include "Statistics.h"

int main(int argc, char *argv[]) {
    using namespace std;

    if (argc != 4) {
        cout << "Usage: " << argv[0] << " problem input output" << endl;
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
                int metros;
                vector<int> cities;

                input >> metros;
                input.ignore();
                cities.push_back(0);

                while (input.peek() != char_traits<char>::to_int_type('\r') && !input.eof()) {
                    int km;
                    input >> km;
                    cities.push_back(km);
                }

                output << Path::greedy(metros, cities) << endl;
            }
            break;
        }
        case 2:
        {
			string line;

			while (getline(input, line)) {
                Median ej2;
                list<int> numbers;
				istringstream stream(line);
				string number;

				while (getline(stream, number, ' ')) {
                    numbers.push_back(stoi(number));
                }

                for (auto &it : ej2.insert(numbers)) {
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
                Explorers ej3(exploradoras);

                PruningFilter filter;
                Bracelet res = ej3.backtracking(filter);
                output << res << endl;
                //output << res.first << " " << res.second << endl;
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
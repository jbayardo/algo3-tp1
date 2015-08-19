#include <iostream>
#include <fstream>
#include "Path.h"
#include "Median.h"
#include "Exploradoras.h"
#include <tuple>


using namespace std;

int main(int argc, char * argvs[]) {
    //	if (argc != 4) {
    //		cout << "usage: " << argvs[0] << " numeroDeEjercicio, archivoEntrada, archivoSalida" << endl;
    //		return 0;
    //	}

    //	ifstream input;
    //	input.open(argvs[2], ifstream::in);
    //	ofstream output;
    //	output.open(argvs[3], ofstream::out);
    //
    //	if (!input.is_open()) {
    //		cout << "File not found" << endl;
    //		return 0;
    //	}

    //	switch (atoi(argvs[1])) {
    //		case 1: {
    //			while (!input.eof()) {
    //				int metros;
    //				vector<int> cities;
    //
    //				input >> metros;
    //				input.ignore();
    //                cities.push_back(0);
    //
    //				while (input.peek() != std::char_traits<char>::to_int_type('\r') && !input.eof()) {
    //					int km;
    //					input >> km;
    //					cities.push_back(km);
    //				}
    //
    //				int res = Path::greedy(metros, cities);
    //				output << res << endl;
    //			}
    //			break;
    //		} case 2: {
    //			Median ej2;
    //
    //			break;
    //		} case 3: {

    std::unordered_map<char, std::string> input3;
    string a("bcde");
    string b("acde");
    string c("abde");
    string d("abc");
    string e("abc");
    auto pa = std::make_pair('a', a);
    auto pb = std::make_pair('b', b);
    auto pc = std::make_pair('c', c);
    auto pd = std::make_pair('d', d);
    auto pe = std::make_pair('e', e);
    input3.insert(pa);
    input3.insert(pb);
    input3.insert(pc);
    input3.insert(pd);
    input3.insert(pe);
    
    Exploradoras ej3(input3);

    auto res = ej3.backtracking();

    cout << std::get<0>(res) << "     " << std::get<1>(res) << std::endl;
        

    //			break;
    //		} default:
    //			cout << "usage: " << argvs[0] << " numeroDeEjercicio(1, 2, 3)" << endl;
    //			break;
    //	}
    return 0;
}
#ifndef ENTRADA_H_
#define ENTRADA_H_

#include <string>
#include <iostream>

using namespace std;

class Entrada {
public:
	string estado;
	string simbolo;

	Entrada();
	Entrada(string, string);

	friend bool operator==(const Entrada& e1, const Entrada& e2);
	friend bool operator<(const Entrada& e1, const Entrada& e2);
};

#endif /*ENTRADA_H_*/

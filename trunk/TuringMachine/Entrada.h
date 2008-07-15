#ifndef ENTRADA_H_
#define ENTRADA_H_

#include <string>
#include <iostream>

using namespace std;

class Entrada {
public:


	Entrada();
	Entrada(string, string);
	
	void setEstado(string);
	void setSimbolo(string);
	string getEstado() const;
	string getSimbolo() const;

	friend bool operator==(const Entrada& e1, const Entrada& e2);
	friend bool operator<(const Entrada& e1, const Entrada& e2);

private:
	string estado;
	string simbolo;
};

#endif /*ENTRADA_H_*/

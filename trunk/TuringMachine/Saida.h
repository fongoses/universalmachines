#ifndef SAIDA_H_
#define SAIDA_H_

#include <string>
#include <iostream>

using namespace std;

class Saida {
	
public:
	string estado;
	string simbolo;
	string movimento;

	Saida();
	Saida(string , string , string);

	int move();

	friend bool operator==(const Saida& s1, const Saida& s2);
};

#endif /*SAIDA_H_*/

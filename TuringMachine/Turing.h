#ifndef TURING_H_
#define TURING_H_

#include <string>
#include <iostream>
#include "Entrada.h"
#include "Saida.h"
#include <set>
#include <map>
#include <vector>
using namespace std;


class Turing {

public:
	vector<string> fita;
	string estado;
	int posicao; //posicao da cabeca
	set<string> finais;
	map<Entrada,Saida> delta;
	string producoes;

	Turing();
	bool executa();
	void imprimeFita();

	string imprimeRegra(Entrada, Saida);
	bool final();

};

#endif /*TURING_H_*/

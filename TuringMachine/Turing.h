#ifndef TURING_H_
#define TURING_H_

#include <string>
#include <iostream>
#include <sstream>
#include "Entrada.h"
#include "Saida.h"
#include <set>
#include <map>
#include <list>
#include <vector>
#include "etc\Arquivo.h"
using namespace std;

class Turing {

public:
	Turing();
	bool executa();
	void imprimeFita();
	void setFileOut(Arquivo*);
	string imprimeRegra(Entrada, Saida);
	bool final();

	void setFita(list<string>);
	void setEstadoInicial(string);
	void setPosicao(int);
	void setEstadosFinais(string);
	void insertDados(Entrada, Saida);
	void showDelta();
	void addProducoes(string);
	void setLoop(char*);
	void decrementa();

	int getLoop();
	string getEstadoInicial() const;
	string getEstadosFinais() const;
	int getPosicao() const;
	list<string> getProducoes() const;

private:

	int loop;
	Arquivo *fileOut;
	vector<string> fita;
	string estado;
	string estadoInicial;
	int posicao;
	set<string> estadosFinais;
	map<Entrada,Saida> delta;
	list<string> producoes;

};

#endif /*TURING_H_*/

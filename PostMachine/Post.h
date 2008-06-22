#ifndef POST_H_
#define POST_H_

#include <list>
#include <string>
#include <iostream>
#include <map>
#include "Entrada.h"
#include "Saida.h"
#include "Cadeia.h"

using namespace std;

class Post {
public:
	Post();

	void tail();
	string head();
	bool executar();
	void concatenarBegin(string);
	void concatenarEnd(string);
	void setPalavraEntrada(list<string>);
	void insertDados(Entrada, Saida);
	void showPalavraEntrada();
	void showDelta();
	virtual ~Post();

private:

	Cadeia cadeia;
	map<Entrada,Saida> delta;
	bool isEmpty();
	list<string> palavraEntrada;
	
	/*list<Entrada> deltaEntrada;
	list<Saida> deltaSaida;
	list<Entrada>::iterator itIn;
	list<Saida>::iterator itOut;*/
};

#endif /*POST_H_*/

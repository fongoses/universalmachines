#ifndef ONESTACK_H_
#define ONESTACK_H_

#include <list>
#include <string>
#include <iostream>
#include <map>
#include "Entrada.h"
#include "Saida.h"
#include "Cadeia.h"

using namespace std;

enum typeQueue{
	FILA,STACKONE,STACKTWO
};

class OneStack {
public:
	OneStack();

	void tail(typeQueue);
	string head(typeQueue);
	bool executar();
	void concatenarBegin(string,typeQueue);
	void concatenarEnd(string,typeQueue);
	void setPalavraEntrada(list<string>);
	void insertDados(Entrada, Saida);
	void showPalavraEntrada();
	void showDelta();
	virtual ~OneStack();

private:

	Cadeia cadeia;
	map<Entrada,Saida> delta;
	bool isEmpty(typeQueue);
	list<string> palavraEntrada;
	list<string> pilhaOne;
};

#endif /*ONESTACK_H_*/

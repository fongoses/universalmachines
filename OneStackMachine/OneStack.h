#ifndef ONESTACK_H_
#define ONESTACK_H_

#include <list>
#include <string>
#include <iostream>
#include <map>
#include <exception>
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
	void showPilha(int);
	void showDelta();
	virtual ~OneStack();

private:
	
	void executarFila(Entrada,Saida);
	voud executarPilhaOne(Entrada,Saida);

	Cadeia cadeia;
	map<Entrada,Saida> delta;
	bool isEmpty(typeQueue);
	list<string> palavraEntrada;
	list<string> pilhaOne;
};

#endif /*ONESTACK_H_*/

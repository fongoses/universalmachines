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
#include "etc\Arquivo.h"
#include <sstream>

using namespace std;

enum typeQueue{
	FILA,STACKONE,STACKTWO
};

class OneStack {
public:
	OneStack();

	void tail(typeQueue);
	string head(typeQueue);
	string executar();
	void concatenarBegin(string,typeQueue);
	void concatenarEnd(string,typeQueue);
	void setPalavraEntrada(list<string>);
	void insertDados(Entrada, Saida);
	void showPalavraEntrada();
	void showPilha(int);
	void showDelta();
	void setFileOut(Arquivo*);
	void setLoop(char*);
	int getLoop();
	string IntToString(int); 
	virtual ~OneStack();

private:
	
	void lookAhead(Entrada,Saida,bool*,bool*);
	Cadeia cadeia;
	int loop;
	map<Entrada,Saida> delta;
	bool isEmpty(typeQueue);
	list<string> palavraEntrada;
	list<string> pilhaOne;
	Arquivo *fileOut;
};

#endif /*ONESTACK_H_*/

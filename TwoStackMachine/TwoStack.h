#ifndef TWOSTACK_H_
#define TWOSTACK_H_

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

enum typeQueue {
	FILA,STACKONE,STACKTWO
};

class TwoStack {
public:
	TwoStack();
	void tail(typeQueue);
	string head(typeQueue);
	string executar();
	void concatenarBegin(string, typeQueue);
	void concatenarEnd(string, typeQueue);
	void setPalavraEntrada(list<string>);
	void insertDados(Entrada, Saida);
	void showPalavraEntrada();
	void showPilha(int,list<string>);
	void showDelta();
	void setFileOut(Arquivo*);
	void setLoop(char*);
	int getLoop();
	virtual ~TwoStack();

private:

	void lookAhead(Entrada, Saida, bool*, bool*,bool*);
	Cadeia cadeia;
	int loop;
	map<Entrada,Saida> delta;
	bool isEmpty(typeQueue);
	list<string> palavraEntrada;
	list<string> pilhaOne;
	list<string> pilhaTwo;
	string IntToString(int); 
	Arquivo *fileOut;
};

#endif /*TWOSTACK_H_*/

#ifndef POST_H_
#define POST_H_

#include <list>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include "etc\Arquivo.h"
#include "Entrada.h"
#include "Saida.h"
#include "Cadeia.h"

using namespace std;

class Post {
public:
	Post();

	void tail();
	string head();
	string executar();
	void concatenarBegin(string);
	void concatenarEnd(string);
	void setPalavraEntrada(list<string>);
	void insertDados(Entrada, Saida);
	void showPalavraEntrada();
	void showDelta();
	void setFileOut(Arquivo*);
	void setLoop(char*);
	int getLoop();
	string IntToString(int);
	virtual ~Post();
	

private:

	int loop;
	Cadeia cadeia;
	map<Entrada,Saida> delta;
	bool isEmpty();
	list<string> palavraEntrada;
	Arquivo *fileOut;

};

#endif /*POST_H_*/

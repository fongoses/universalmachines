#ifndef SAIDA_H_
#define SAIDA_H_

#include <string>
#include <iostream>
using namespace std;

enum TypeMove {
	RIGHT,LEFT,STOP
};


class Saida {

public:
	Saida();
	Saida(string, string, string);
	
	void setEstado(string);
	void setSimbolo(string);
	void setMovimento(string);
	
	string getEstado() const;
	string getSimbolo() const;
	string getMovimento() const;
	TypeMove getTypeMove() const;

	int move();

	friend bool operator==(const Saida& s1, const Saida& s2);
	
private:
	string estado;
	string simbolo;
	string movimento;
	TypeMove typeMove;
};

#endif /*SAIDA_H_*/

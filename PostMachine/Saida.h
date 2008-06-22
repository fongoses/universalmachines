#ifndef SAIDA_H_
#define SAIDA_H_

#include <list>
#include <string>
#include <iostream>

using namespace std;

class Saida {
public:
	Saida();
	Saida(string,string,string);
	
	void setTail(bool);
	void setConcatenar(string);
	void setProximoEstado(string);
	
	bool isTail();
	string getConcatenar() const;
	string getProximoEstado() const;
	
	friend bool operator== (const Saida& s1, const Saida& s2);
	
	virtual ~Saida();

private:
	bool tail;
	string concatenar;
	string proximoEstado;

};

#endif /*SAIDA_H_*/

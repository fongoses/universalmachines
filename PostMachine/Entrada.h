#ifndef ENTRADA_H_
#define ENTRADA_H_

#include <list>
#include <string>
#include <iostream>

using namespace std;

class Entrada {
public:
	Entrada();
	Entrada(string, string);

	void setEstado(string);
	void setHead(string);

	string getEstado() const;
	string getHead()const;

	friend bool operator== (const Entrada& e1, const Entrada& e2);
	friend bool operator< (const Entrada& e1, const Entrada& e2);
	
	virtual ~Entrada();
private:
	string estado;
	string head;

};

#endif /*ENTRADA_H_*/

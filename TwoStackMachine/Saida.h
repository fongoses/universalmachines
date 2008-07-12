#ifndef SAIDA_H_
#define SAIDA_H_

#include <list>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Saida {
public:
	Saida();
	Saida(string, string, string, string, string, string, string);

	void setTail(bool);
	void setConcatenar(string);
	void setProximoEstado(string);
	void setTailStack(int, bool);
	void setConcatenarStack(int, string);

	bool isTailStack(int) const;
	string getConcatenarStack(int) const;
	bool isTail() const;
	string getConcatenar() const;
	string getProximoEstado() const;

	friend bool operator==(const Saida& s1, const Saida& s2);
	friend bool operator<(const Saida& s1, const Saida& s2);

	virtual ~Saida();

private:
	bool tail;
	vector<bool> tailStack;
	string concatenar;
	vector<string> concatenarStack;
	string proximoEstado;

};

#endif /*SAIDA_H_*/

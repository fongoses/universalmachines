#ifndef ALFABETO_H_
#define ALFABETO_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Alfabeto {
public:
	Alfabeto();
	void setAlfabeto(vector<string>);
	string getAlfabeto();
	bool isCaracterDoAlfabeto(vector<string>);
	virtual ~Alfabeto();

private:
	vector<string> alfabeto;
};

#endif /*ALFABETO_H_*/

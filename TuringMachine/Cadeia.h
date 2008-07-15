#ifndef CADEIA_H_
#define CADEIA_H_

#include <list>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Cadeia
{
public:
	Cadeia();
	
	void setPalavra(vector<string>);
	list<string> getPalavra();
	string getPalavraToString();
	virtual ~Cadeia();
	
private:
	list<string> palavra;
};

#endif /*CADEIA_H_*/


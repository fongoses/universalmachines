#ifndef ARQUIVO_H_
#define ARQUIVO_H_

#include <fstream>
#include <string>

#include <iostream>
using namespace std;

class Arquivo {
public:
	Arquivo();
	void setEnd(char*);
	virtual ~Arquivo();
	void abrir(ios_base::openmode);
	void fechar();
	void write(string);
	bool isTheEnd();
	bool isOpen();
	std::string getLinha();
private:
	char *enderecoArquivo;
	std::fstream file;
};

#endif /*ARQUIVO_H_*/

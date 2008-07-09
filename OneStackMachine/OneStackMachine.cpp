//============================================================================
// Name        : OneStackMachine.cpp
// Author      : Thiago Genez & Pedro Sanches
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "etc\Arquivo.h"
#include "etc\stringUtils.h"
#include "OneStack.h"
#include <map>
using namespace std;





int main(int argc, char *argv[]) {

	vector<string> palavra;
	vector<string>::iterator it;

	Arquivo fileProgram;
	Arquivo fileFila;

	Cadeia cadeia;

	OneStack oneStack;

	char *programa, *fila;

	if (argc == 3) {
		programa = argv[1];
		fila = argv[2];
		fileProgram.setEnd(programa);
		fileFila.setEnd(fila);
	} else {
		programa = "programa.txt";
		fila = "fila.txt";
		fileProgram.setEnd("programa.txt");
		fileFila.setEnd("fila.txt");
	}

	fileProgram.abrir(fstream::in);
	fileFila.abrir(fstream::in);

	while (!fileFila.isTheEnd()) {
		string line = fileFila.getLinha();
		if (line.compare("") != 0) {
			vector<string> linha = StringUtils::tokenize(line);
			palavra = linha;
			cadeia.setPalavra(linha);
			oneStack.setPalavraEntrada(cadeia.getPalavra());
		}
	}

	while (!fileProgram.isTheEnd()) {
		string line = fileProgram.getLinha();
		if (line.compare("") != 0) {
			try {
				vector<string> linha = StringUtils::tokenize(line);
				if(linha.size() != 8) {
					throw string("Programa mal formado");
				} else {
					Entrada in(linha[0],linha[1],linha[2]);
					Saida out(linha[3],linha[4],linha[5],linha[6],linha[7]);
					oneStack.insertDados(in,out);
				}

			} catch (string s) {
				cout << s << endl;
				system("pause");
				exit(1);
			}

		}
	}
	cout << "Programa da Maquina de uma Pilha: " << endl << endl;
	oneStack.showDelta();
	if (oneStack.executar()) {
		cout << endl << endl <<"A Maquina de uma Pilha Aceitou a palavra: ";
	} else {
		cout << endl << endl << "A Maquina de uma Pilha Rejeitou a palavra : ";
	}

	for (it = palavra.begin(); it < palavra.end(); it++) {
		cout <<*it;
	}
	cout << endl << endl;

	fileProgram.fechar();
	fileFila.fechar();

	system("pause");

	return 0;
}

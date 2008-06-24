//============================================================================
// Name        : TuringMachine.cpp
// Author      : Thiago Genez & Pedro Sanches
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Turing.h"
#include "etc/stringUtils.h"

bool operator==(const Saida& s1, const Saida& s2) {
	return (s1.estado==s2.estado)&&(s1.simbolo==s2.simbolo)&&(s1.movimento
			==s2.movimento);
}

bool operator==(const Entrada& e1, const Entrada& e2) {
	return (e1.estado==e2.estado)&&(e1.simbolo==e2.simbolo);
}

bool operator<(const Entrada& e1, const Entrada& e2) {
	if (e1.estado<e2.estado)
		return true;
	else {
		if ((e1.estado==e2.estado)&&(e1.simbolo<e2.simbolo))
			return true;
	}
	return false;

}

using namespace std;

int main(int argc, char *argv[]) {

	Turing turingMachine;

	char *programa, *fita;

	if (argc==3) {
		programa = argv[1];
		fita = argv[2];
	} else {
		programa = "programa.txt";
		fita = "fita.txt";
	}

	ifstream inFile(fita);

	string line = "";

	while (line == "")
		getline(inFile, line, '\n');

	vector<string> aFita = StringUtils::tokenize(line);
	for (int i=0; i<(int)aFita.size(); i++)
		turingMachine.fita.push_back(aFita[i]);

	inFile.close();

	inFile.open(programa);

	line = "";

	while (line == "")
		getline(inFile, line, '\n');

	vector<string> inicial = StringUtils::tokenize(line);
	turingMachine.estado = inicial[0];

	line = "";

	while (line == "")
		getline(inFile, line, '\n');

	vector<string> final = StringUtils::tokenize(line);
	for (int i=0; i<(int)final.size(); i++)
		turingMachine.finais.insert(final[i]);

	try {
		while(getline(inFile,line,'\n'))
		{
			if (line!="")
			{
				vector<string> regra = StringUtils::tokenize(line);
				if (regra.size() < 5) throw string("Programa mal formado");
				Entrada entrada(regra[0], regra[1]);
				Saida saida(regra[2], regra[3], regra[4]);
				turingMachine.delta[entrada] = saida;
			}
		}
	} catch (string s)
	{
		cout << s << endl;
		exit(1);
	}

	do {
		turingMachine.imprimeFita();
	} while (turingMachine.executa());

	if (turingMachine.final())
		cout << endl << "A maquina de Turing parou e respondeu TRUE" << endl;
	else
		cout << endl << "A maquina de Turing parou e respondeu FALSE" << endl;

	cout << endl << endl << "As Producoes foram: " << endl;
	cout << turingMachine.producoes;

	system("PAUSE");
	return EXIT_SUCCESS;
}

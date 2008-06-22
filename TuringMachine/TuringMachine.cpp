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
#include "turing.h"
#include "stringUtils.h"

using namespace std;

int main(int argc, char *argv[]) {

	TuringMachine turingMachine;

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
				//cout << "delta(" << regra[0] << "," << regra[1] << ") = (";
				//cout << regra[2] << "," << regra[3] << "," << regra[4] << ")" << endl;
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
		cout << "A maquina de Turing parou e respondeu TRUE" << endl;
	else
		cout << "A maquina de Turing parou e respondeu FALSE" << endl;

	cin >> line;

	//system("PAUSE");
	return EXIT_SUCCESS;
}

/*
 //Questao 8.2.5c
 int main(int argc, char *argv[])
 {
 
 TuringMachine turingMachine;
 
 Entrada entrada1("q0","0");
 Saida saida1("q1","1","R");
 
 turingMachine.delta[entrada1] = saida1;
 
 
 Entrada entrada2("q1","1");
 Saida saida2("q2","0","L");
 
 turingMachine.delta[entrada2] = saida2;

 Entrada entrada3("q2","1");
 Saida saida3("q0","1","R");
 
 turingMachine.delta[entrada3] = saida3;
 
 Entrada entrada4("q1","B");
 Saida saida4("qf","B","R");
 
 turingMachine.delta[entrada4] = saida4;
 
 turingMachine.finais.insert("qf");
 turingMachine.estado = "q0";
 
 turingMachine.fita.push_back("0");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 
 while(1)
 {
 turingMachine.imprimeFita();
 turingMachine.executa();
 system("PAUSE");
 }
 
 
 system("PAUSE");
 return EXIT_SUCCESS;
 }
 */

/*
 //Questao 8.2.5b
 int main(int argc, char *argv[])
 {
 
 TuringMachine turingMachine;
 
 Entrada entrada1("q0","0");
 Saida saida1("q0","B","R");
 
 turingMachine.delta[entrada1] = saida1;
 
 
 Entrada entrada2("q0","1");
 Saida saida2("q1","B","R");
 
 turingMachine.delta[entrada2] = saida2;

 Entrada entrada3("q1","1");
 Saida saida3("q1","B","R");
 
 turingMachine.delta[entrada3] = saida3;
 
 Entrada entrada4("q1","B");
 Saida saida4("qf","B","R");
 
 turingMachine.delta[entrada4] = saida4;
 
 turingMachine.finais.insert("qf");
 turingMachine.estado = "q0";
 
 turingMachine.fita.push_back("0");
 turingMachine.fita.push_back("0");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 turingMachine.fita.push_back("1");
 
 while(1)
 {
 turingMachine.imprimeFita();
 turingMachine.executa();
 system("PAUSE");
 }
 
 
 system("PAUSE");
 return EXIT_SUCCESS;
 }
 */

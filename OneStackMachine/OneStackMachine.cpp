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
#include "Alfabeto.h"
#include <map>
using namespace std;

int main(int argc, char *argv[]) {

	vector<string> palavra;
	vector<string>::iterator it;

	Arquivo fileProgram;
	Arquivo fileFila;
	Arquivo fileOut;
	Arquivo fileAlfabeto;

	Cadeia cadeia;

	OneStack oneStack;

	Alfabeto alfabeto;

	char *programa, *fila, *out, *alfa;

	if (argc == 5) {
		programa = argv[1];
		fila = argv[2];
		alfa = argv[3];
		out = argv[4];
		fileProgram.setEnd(programa);
		fileFila.setEnd(fila);
		fileAlfabeto.setEnd(alfa);
		fileOut.setEnd(out);
	} else {
		fileProgram.setEnd("programa.txt");
		fileFila.setEnd("fila.txt");
		fileAlfabeto.setEnd("alfabeto.txt");
		fileOut.setEnd("saida.txt");
	}

	fileProgram.abrir(fstream::in);
	fileFila.abrir(fstream::in);
	fileOut.abrir(fstream::out);
	fileAlfabeto.abrir(fstream::in);

	oneStack.setFileOut(&fileOut);

	while (!fileAlfabeto.isTheEnd()) {
		string line = fileAlfabeto.getLinha();
		if (line.compare("") != 0) {
			vector<string> linha = StringUtils::tokenize(line);
			alfabeto.setAlfabeto(linha);
		}
	}

	while (!fileFila.isTheEnd()) {
		string line = fileFila.getLinha();
		if (line.compare("") != 0) {
			vector<string> linha = StringUtils::tokenize(line);
			palavra = linha;
			cadeia.setPalavra(linha);
			try {
				if(alfabeto.isCaracterDoAlfabeto(linha)) {
					oneStack.setPalavraEntrada(cadeia.getPalavra());
				} else {
					throw string("ALGUM CARACTER DA CADEIA \""+cadeia.getPalavraToString()+"\" NAO PERTENCE AO ALFABETO "+alfabeto.getAlfabeto());
				}
			} catch (string e) {
				cout << e << endl;
				system("pause");
				exit(1);
			}

		}
	}

	while (!fileProgram.isTheEnd()) {
		string line = fileProgram.getLinha();
		if (line.compare("") != 0) {
			try {
				vector<string> linha = StringUtils::tokenize(line);
				if(linha.size() != 8) {
					throw string("PROGRAMA MAL FORMULADO, REESCREVE AS INSTRUCOES DA MAQUINA");
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
	fileOut.write("********************************************************************************** \n");
	fileOut.write("*Alunos:     Pedro Sanches Junior                                                * \n");
	fileOut.write("*            Thiago Augusto Lopes Genez                                          * \n");
	fileOut.write("*                                                                                * \n");
	fileOut.write("*Professora: Maria Angelica Brunetto                                             * \n");
	fileOut.write("*                                                                                * \n");
	fileOut.write("*Disciplina: Teoria da Computcao                                                 * \n");
	fileOut.write("********************************************************************************** \n\n");
	fileOut.write("---------------------------------------------------------------------------------- \n");
	fileOut.write("|    S I M U L A D O R     D A     M A Q U I N A     D E     1 P I L H A           |\n");
	fileOut.write("|__________________________________________________________________________________|\n\n\n");

	oneStack.showDelta();

	if (oneStack.executar()) {
		fileOut.write("\n\nA Maquina de uma Pilha ACEITOU a palavra: ");
	} else {
		fileOut.write("\n\nA Maquina de uma Pilha REJEITOU a palavra : ");
	}

	string word = "";
	for (it = palavra.begin(); it < palavra.end(); it++) {
		word += *it;
	}
	fileOut.write(word);

	fileProgram.fechar();
	fileFila.fechar();
	fileAlfabeto.fechar();
	fileOut.fechar();

	return 0;
}

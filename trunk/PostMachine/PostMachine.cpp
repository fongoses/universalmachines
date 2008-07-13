//============================================================================
// Name        : PostMachine.cpp
// Author      : Thiago Genez & Pedro Sanches
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "etc\Arquivo.h"
#include "etc\stringUtils.h"
#include "Post.h"
#include "Alfabeto.h"
#include <map>
using namespace std;

int main(int argc, char *argv[]) {

	vector<string> palavra;
	vector<string>::iterator it;

	Arquivo fileProgram;
	Arquivo fileFila;
	Arquivo fileAlfabeto;
	Arquivo fileOut;

	Cadeia cadeia;

	Alfabeto alfabeto;

	Post maquinaPost;

	char *programa;
	char *fila;
	char *alfa;
	char *out;

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
	fileAlfabeto.abrir(fstream::in);
	fileOut.abrir(fstream::out);

	maquinaPost.setFileOut(&fileOut);

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
					maquinaPost.setPalavraEntrada(cadeia.getPalavra());
				} else {
					throw string("Algum caracter da cadeia "+cadeia.getPalavraToString()+" nao pertence ao alfabeto "+alfabeto.getAlfabeto());
				}
			} catch (string e) {
				cout << endl << e << endl;
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
				if(linha.size() != 5) {
					throw string("Programa mal formado");
				} else {
					Entrada in(linha[0],linha[1]);
					Saida out(linha[2],linha[3],linha[4]);
					maquinaPost.insertDados(in,out);
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
	fileOut.write("|    S I M U L A D O R     D A     M A Q U I N A     D E     P O S T               |\n");
	fileOut.write("|__________________________________________________________________________________|\n\n\n");

	maquinaPost.showDelta();

	if (maquinaPost.executar()) {
		fileOut.write("\n\nA maquina de Post ACEITOU a palavra: ");
	} else {
		fileOut.write("\n\nA maquina de Post REJEITOU a palavra: ");
	}

	string word = "";
	for (it = palavra.begin(); it < palavra.end(); it++) {
		word += *it;
	}
	if (word.size() == 0) {
		fileOut.write("\"palavra vazia\"");
	} else {
		fileOut.write(word);
	}

	fileProgram.fechar();
	fileFila.fechar();
	fileAlfabeto.fechar();
	fileOut.fechar();

	return 0;
}

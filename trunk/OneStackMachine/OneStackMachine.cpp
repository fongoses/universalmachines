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

	/*
	 * vetor para armazenar a palavra de entrada
	 */
	vector<string> palavra;
	vector<string>::iterator it;

	/*
	 * objeto arquivos para realizar
	 * o tratamento dos mesmos
	 */
	Arquivo fileProgram;
	Arquivo fileFila;
	Arquivo fileOut;
	Arquivo fileAlfabeto;

	/*
	 * objeto cadeia para tratar da cadeia
	 */
	Cadeia cadeia;

	/*
	 * objeto 1 pilha propriamento dito
	 */
	OneStack oneStack;

	/*
	 * objeto alfabeto para verificar se a cadeia contem
	 * as letra do alfabeto
	 */
	Alfabeto alfabeto;

	/*
	 * variaveis auxiliares
	 * para armazenar os nomes do arquivos que
	 * nao vao ser executado por padrao
	 */
	char *programa, *fila, *out, *alfa;

	/*
	 * armazenar o numero de vezes que ira
	 * acontecer o loop
	 */
	char *tamanhoLoop = 0;

	/*
	 * fazendo a verificacao de entrada
	 */
	if (argc == 6) {
		programa = argv[1];
		fila = argv[2];
		alfa = argv[3];
		out = argv[4];
		tamanhoLoop = argv[5];
		fileProgram.setEnd(programa);
		fileFila.setEnd(fila);
		fileAlfabeto.setEnd(alfa);
		fileOut.setEnd(out);
	} else if (argc == 1) {
		fileProgram.setEnd("programa.txt");
		fileFila.setEnd("fila.txt");
		fileAlfabeto.setEnd("alfabeto.txt");
		fileOut.setEnd("saida.txt");
		tamanhoLoop = "50";
	} else {
		cout << "Programa executando de maneira errada!" << endl
				<< "Exemplo da linha de comando sem os \"[\" \"]\": " << endl;
		cout
				<< "[OneStackMachine.exe] [programa.txt] [fila.txt] [alfabeto.txt] [saida.txt] [50]"
				<< endl;
		system("pause");
		exit(0);
	}

	try {
		/*
		 * abertura dos arquivos
		 */
		fileProgram.abrir(fstream::in);
		if(!fileProgram.isOpen()) {
			throw string("Arquivo \""+fileProgram.getEnd()+"\" inexistente!!");
		}
		fileFila.abrir(fstream::in);
		if(!fileFila.isOpen()) {
			throw string("Arquivo \""+fileFila.getEnd()+"\" inexistente!!");
		}
		fileAlfabeto.abrir(fstream::in);
		if(!fileAlfabeto.isOpen()) {
			throw string("Arquivo \""+fileAlfabeto.getEnd()+"\" inexistente!!");
		}
		fileOut.abrir(fstream::out);
	} catch (string e) {
		cout << endl << e << endl;
		system("pause");
		exit(1);
	}

	/*
	 * setanto o arquivo de saida para a maquina
	 * de1 pilha realziar a escrita no mesmo
	 */
	oneStack.setFileOut(&fileOut);

	/*
	 * setando o tamanho do loop
	 */
	oneStack.setLoop(tamanhoLoop);

	/*
	 * setanto o alfabeto
	 */
	while (!fileAlfabeto.isTheEnd()) {
		string line = fileAlfabeto.getLinha();
		if (line.compare("") != 0) {
			vector<string> linha = StringUtils::tokenize(line);
			alfabeto.setAlfabeto(linha);
		}
	}

	/*
	 * setanto a fita
	 */
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

	/*
	 * setanto o programa da maquina de 2 pilha
	 */
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

	/*
	 * realizando os processos do arquivo de saida
	 */
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

	/*
	 * mosttra a funcao delta da maquina de 1 pilha
	 */
	oneStack.showDelta();

	/*
	 * realizando a execucao da maquina
	 * e a conclusao da palavra de entrada na maquina
	 * de 1 pilha
	 */
	fileOut.write(oneStack.executar());

	string word = "";
	for (it = palavra.begin(); it < palavra.end(); it++) {
		word += *it;
	}
	if (word.size() == 0) {
		fileOut.write("\"palavra vazia\"");
	} else {
		fileOut.write(word);
	}

	/*
	 * fecha os arquivos
	 */
	fileProgram.fechar();
	fileFila.fechar();
	fileAlfabeto.fechar();
	fileOut.fechar();

	return 0;
}

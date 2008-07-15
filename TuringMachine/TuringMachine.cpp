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
#include "etc/Arquivo.h"
#include "Alfabeto.h"
#include "Cadeia.h"

using namespace std;

int main(int argc, char *argv[]) {

	/*
	 * vetor para armazenar a palavra de entrada
	 */
	vector<string> palavra;
	vector<string>::iterator it;

	/*
	 * objeto cadeia para tratar da cadeia
	 */
	Cadeia cadeia;

	/*
	 * objeto alfabeto para verificar se a cadeia contem
	 * as letra do alfabeto
	 */
	Alfabeto alfabeto;

	/*
	 * objeto arquivos para realizar
	 * o tratamento dos mesmos
	 */
	Arquivo fileOut;
	Arquivo fileProgram;
	Arquivo fileAlfabeto;
	Arquivo fileFita;

	/*
	 * objeto turing propriamento dito
	 */
	Turing turingMachine;

	/*
	 * variaveis auxiliares
	 * para armazenar os nomes do arquivos que
	 * nao vao ser executado por padrao
	 */
	char *programa;
	char *fita;
	char *out;
	char *alfa;

	if (argc == 5) {
		programa = argv[1];
		fita = argv[2];
		alfa = argv[3];
		out = argv[4];
		fileProgram.setEnd(programa);
		fileFita.setEnd(fita);
		fileAlfabeto.setEnd(alfa);
		fileOut.setEnd(out);
	} else {
		fileProgram.setEnd("programa.txt");
		fileFita.setEnd("fita.txt");
		fileAlfabeto.setEnd("alfabeto.txt");
		fileOut.setEnd("saida.txt");
	}

	/*
	 * abertura dos arquivos
	 */
	fileProgram.abrir(fstream::in);
	fileFita.abrir(fstream::in);
	fileAlfabeto.abrir(fstream::in);
	fileOut.abrir(fstream::out);

	/*
	 * setanto o arquivo de saida para a maquina
	 * de turing realziar a escrita no mesmo
	 */
	turingMachine.setFileOut(&fileOut);

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
	while (!fileFita.isTheEnd()) {
		string line = fileFita.getLinha();
		if (line.compare("") != 0) {
			vector<string> linha = StringUtils::tokenize(line);
			palavra = linha;
			cadeia.setPalavra(linha);
			try {
				if(alfabeto.isCaracterDoAlfabeto(linha)) {
					turingMachine.setFita(cadeia.getPalavra());
				} else {
					throw string("Algum caracter da cadeia "+cadeia.getPalavraToString()+" nao pertence ao alfabeto "+alfabeto.getAlfabeto()+"\nVerifique!!!");
				}
			} catch (string e) {
				cout << endl << e << endl;
				system("pause");
				exit(1);
			}

		}
	}

	/*
	 * pega o estado Inicial
	 */
	string line = "";
	while (line.compare("") == 0) {
		line = fileProgram.getLinha();
	}
	vector<string> estadoInicial = StringUtils::tokenize(line);
	turingMachine.setEstadoInicial(estadoInicial[0]);

	/*
	 * pega o(s) estado(s) final(is)
	 */

	line = "";
	while (line.compare("") == 0) {
		line = fileProgram.getLinha();
	}
	vector<string> estadosFinais = StringUtils::tokenize(line);
	for (it = estadosFinais.begin(); it < estadosFinais.end(); it++) {
		turingMachine.setEstadosFinais((*it));
	}

	/*
	 * setanto o programa de turing
	 */
	while (!fileProgram.isTheEnd()) {
		string line = fileProgram.getLinha();
		if (line.compare("") != 0) {
			try {
				vector<string> linha = StringUtils::tokenize(line);
				if(linha.size() != 5) {
					throw string("Programa foi mal formado\nTente Novamente");
				} else {
					Entrada in(linha[0],linha[1]);
					Saida out(linha[2],linha[3],linha[4]);
					turingMachine.insertDados(in,out);
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
	fileOut.write("|    S I M U L A D O R     D A     M A Q U I N A     D E     T U R I N G           |\n");
	fileOut.write("|__________________________________________________________________________________|\n\n\n");

	/*
	 * mosttra a funcao delta da maquina de turing
	 */
	turingMachine.showDelta();

	/*
	 * realizando a execucao da maquina
	 */
	fileOut.write("Passo - a - Passo da Execucao da Maquina Turing: \n\n");
	do {
		turingMachine.imprimeFita();
	} while (turingMachine.executa());

	/*
	 * pega as producoes realizadas pela maquina
	 */
	fileOut.write("\n---------------------------------------------------------------------------------- \n");
	fileOut.write("\n\nAs Producoes realizadas foram as seguintes: \n\n");
	list<string> producoes = turingMachine.getProducoes();

	string word = "";
	list<string>::iterator it2;
	for (it2 = producoes.begin(); it2 != producoes.end(); it2++) {
		word += *it2;
	}
	fileOut.write(word);

	/*
	 * realiza a conclusao da palavra de entrada na maquina
	 * de turing
	 */
	fileOut.write("\n---------------------------------------------------------------------------------- \n\n CONCLUSAO: ");
	if (turingMachine.final()) {
		fileOut.write("\n\n\nA maquina de Turing parou e respondeu TRUE para palavra: ");
	} else {
		fileOut.write("\n\n\nA maquina de Turing parou e respondeu FALSE para palavra: ");
	}

	word = "";
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
	fileFita.fechar();
	fileAlfabeto.fechar();
	fileOut.fechar();
	return 0;
}

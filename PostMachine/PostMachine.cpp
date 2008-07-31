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
	Arquivo fileAlfabeto;
	Arquivo fileOut;

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
	 * objeto post propriamento dito
	 */
	Post maquinaPost;

	/*
	 * variaveis auxiliares
	 * para armazenar os nomes do arquivos que
	 * nao vao ser executado por padrao
	 */
	char *programa;
	char *fila;
	char *alfa;
	char *out;

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
				<< "[PostMachine.exe] [programa.txt] [fila.txt] [alfabeto.txt] [saida.txt] [50]"
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
	 * de post realziar a escrita no mesmo
	 */
	maquinaPost.setFileOut(&fileOut);

	/*
	 * setando o tamanho do loop
	 */
	maquinaPost.setLoop(tamanhoLoop);

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

	/*
	 * setanto o programa da maquina de post
	 */
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
	fileOut.write("|    S I M U L A D O R     D A     M A Q U I N A     D E     P O S T               |\n");
	fileOut.write("|__________________________________________________________________________________|\n\n\n");

	/*
	 * mosttra a funcao delta da maquina de post
	 */
	maquinaPost.showDelta();

	/*
	 * realizando a execucao da maquina
	 * e a conclusao da palavra de entrada na maquina
	 * de post
	 */
	fileOut.write(maquinaPost.executar());

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

#include "Post.h"

Post::Post() {
	this->fileOut = NULL;
}

Post::~Post() {

}

void Post::tail() {
	if (!this->isEmpty()) {
		this->palavraEntrada.pop_front();
	}
}

string Post::head() {
	string cabeca = "";
	if (!this->isEmpty()) {
		cabeca = this->palavraEntrada.front();
	}
	return (cabeca);
}

void Post::concatenarBegin(string caracter) {
	this->palavraEntrada.push_front(caracter);
}

void Post::concatenarEnd(string caracter) {
	this->palavraEntrada.push_back(caracter);
}

void Post::setPalavraEntrada(list<string> palavraEntrada) {
	this->palavraEntrada = palavraEntrada;
}

bool Post::isEmpty() {
	return (this->palavraEntrada.empty());
}
void Post::insertDados(Entrada in, Saida out) {
	this->delta.insert(pair<Entrada, Saida>(in, out) );
}

bool Post::executar() {
	map<Entrada,Saida>::iterator it;
	Entrada entrada("START", "~");
	string cabeca = "";
	string nextState = "";
	while (true) {
		this->showPalavraEntrada();

		Saida saida = this->delta[entrada];

		this->fileOut->write("Estado Atual :" + entrada.getEstado()
				+"    Cabeca: " + entrada.getHead() + "\n");

		this->fileOut->write("Concatenacao:" + saida.getConcatenar()
				+ "     Proximo Estado: " + saida.getProximoEstado() + "\n");

		this->fileOut->write("---------------------------------------------------------------------------------- \n");

		if (saida.isTail()) {
			this->tail();
		}
		if (saida.getConcatenar().compare("~") != 0) {
			this->concatenarEnd(saida.getConcatenar());
		}
		if (saida.getProximoEstado().compare("ACCEPT") == 0) {
			return true;
		} else if (saida.getProximoEstado().compare("REJECT") == 0) {
			return false;
		} else {
			nextState = saida.getProximoEstado();
		}

		cabeca = this->head();
		if (cabeca.compare("") == 0) {
			cabeca = "@";
		}
		entrada = Entrada(nextState, cabeca);
		cabeca = "";
	}
	return false;
}
void Post::showPalavraEntrada() {
	list<string>::iterator it;
	this->fileOut->write("Resultado Parcial : ");
	string word = "";
	if (!this->palavraEntrada.empty()) {
		for (it = this->palavraEntrada.begin(); it
				!= this->palavraEntrada.end(); it++) {
			word += *it;
		}
	} else {
		word = " vazia";
	}
	this->fileOut->write(word + "\n");
}

void Post::showDelta() {
	map<Entrada,Saida>::iterator it;
	this->fileOut->write("Funcao Programa da Maquina de POST:\n");
	for (it = this->delta.begin() ; it != this->delta.end(); it++) {
		this->fileOut->write("Estado: " + (*it).first.getEstado() + "       Head: " + (*it).first.getHead() + "     =>     Concatenar" + (*it).second.getConcatenar() + "    Proximo Estado:  " + (*it).second.getProximoEstado() + "\n");
	}

	this->fileOut->write("---------------------------------------------------------------------------------- \n");
	this->fileOut->write("\n\n\n");
}

void Post::setFileOut(Arquivo* fileOut) {
	this->fileOut = fileOut;
}

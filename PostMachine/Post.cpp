#include "Post.h"

Post::Post() {
	this->fileOut = NULL;
	this->loop = 0;
}

Post::~Post() {

}

void Post::setLoop(char* loop) {
	string looping = (string)loop;

	stringstream stm;
	stm.str(looping);
	stm >> this->loop;
}

int Post::getLoop() {
	return (this->loop);
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

string Post::executar() {
	map<Entrada,Saida>::iterator it;
	Entrada entrada("START", "~");
	string cabeca = "";
	string nextState = "";
	int laco = this->loop;
	while (laco >= 0) {
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
			return ("\n\nA maquina de Post ACEITOU a palavra: ");
		} else if (saida.getProximoEstado().compare("REJECT") == 0) {
			return ("\n\nA maquina de Post REJEITOU a palavra: ");
		} else {
			nextState = saida.getProximoEstado();
		}

		cabeca = this->head();
		if (cabeca.compare("") == 0) {
			cabeca = "@";
		}
		entrada = Entrada(nextState, cabeca);
		cabeca = "";
		laco--;
	}

	return ("\n\nA maquina de Post entrou em LOOP (laco de \""
			+this->IntToString(this->loop) +"\" repeticoes) para a palavra: ");
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

string Post::IntToString(int num) {
	stringstream out;
	out << num;
	return (out.str());
}

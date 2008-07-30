#include "Turing.h"

Turing::Turing() {
	this->setPosicao(0);
	this->loop = 0;
}

void Turing::setLoop(char* loop) {
	string looping = (string)loop;

	stringstream stm;
	stm.str(looping);
	stm >> this->loop;
}

int Turing::getLoop() {
	return(this->loop);
}

void Turing::decrementa(){
	this->loop--;
}

bool Turing::executa() {
	Entrada entrada(this->estado, this->fita[posicao]);
	if (this->delta.find(entrada) != this->delta.end()) {
		Saida saida = this->delta[entrada];
		this->addProducoes(imprimeRegra(entrada, saida));
		this->estado = saida.getEstado();
		this->fita[this->getPosicao()] = saida.getSimbolo();
		this->posicao += saida.move();
		if (this->posicao == (int)fita.size()) {
			this->fita.push_back("B");
		}
	} else {
		return false;
	}
	return true;
}

void Turing::imprimeFita() {
	vector<string>::iterator it;
	int i = 0;
	this->fileOut->write("- (" + this->estado + ") ==> ");

	for (it = this->fita.begin(); it != this->fita.end(); it++) {
		if (i == this->getPosicao()) {
			this->fileOut->write("[" + (*it) + "]");
		} else {
			this->fileOut->write(" "+(*it) + " ");
		}
		i++;
	}
	this->fileOut->write("\n");
}

string Turing::imprimeRegra(Entrada entrada, Saida saida) {
	string aux = "";
	aux = "- delta(" + entrada.getEstado() + ", " + entrada.getSimbolo()
			+ ") = ";
	aux += "(" + saida.getEstado() + ", " + saida.getSimbolo() + ", "
			+ saida.getMovimento() + ") \n";
	return aux;
}

bool Turing::final() {
	if (this->estadosFinais.find(estado) != this->estadosFinais.end()) {
		return (true);
	}
	return false;
}

void Turing::setFileOut(Arquivo* fileOut) {
	this->fileOut = fileOut;
}

void Turing::setFita(list<string> fita) {
	list<string>::iterator it;
	for (it = fita.begin(); it != fita.end(); it++) {
		this->fita.push_back((*it));
	}

}
void Turing::setEstadoInicial(string estadoInicial) {
	this->estadoInicial = estadoInicial;
	this->estado = estadoInicial;
}
void Turing::setPosicao(int posicao) {
	this->posicao = posicao;
}
void Turing::setEstadosFinais(string finais) {
	this->estadosFinais.insert(finais);
}
void Turing::insertDados(Entrada in, Saida out) {
	this->delta.insert(pair<Entrada, Saida>(in, out) );
}

void Turing::showDelta() {
	map<Entrada,Saida>::iterator it;
	this->fileOut->write("Funcao Programa da Maquina de TURING:\n\n\n");
	this->fileOut->write("Estado Inicial: " + this->getEstadoInicial() + "\n");
	this->fileOut->write("Estado(s) Finais: " + this->getEstadosFinais()
			+ "\n\n");
	for (it = this->delta.begin() ; it != this->delta.end(); it++) {
		this->fileOut->write("Estado: " + (*it).first.getEstado() + "       Leitura Simbolo: " + (*it).first.getSimbolo() + "     =>     Estado Destino: " + (*it).second.getEstado() + "    Simbolo Escrito: " + (*it).second.getSimbolo() + "     Movimento: " + (*it).second.getMovimento() + "\n");
	}

	this->fileOut->write("---------------------------------------------------------------------------------- \n");
	this->fileOut->write("\n\n\n");
}

string Turing::getEstadoInicial() const {
	return (this->estadoInicial);
}

string Turing::getEstadosFinais() const {
	set<string>::iterator it;
	string aux = "";
	for (it = this->estadosFinais.begin(); it != this->estadosFinais.end(); it++) {
		aux += (*it) + ",";
	}
	return (aux);
}
int Turing::getPosicao() const {
	return (this->posicao);
}
void Turing::addProducoes(string producoes) {
	this->producoes.push_back(producoes);
}
list<string> Turing::getProducoes() const {
	return (this->producoes);
}

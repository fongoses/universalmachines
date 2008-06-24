#include "Saida.h"

Saida::Saida() {
}

Saida::~Saida() {
}

Saida::Saida(string tail, string tailPilha, string concatenar,
		string concatenarPilha, string proximoEstado) {
	if (tail.compare("tail") == 0) {
		this->setTail(true);
	} else {
		this->setTail(false);
	}

	if (tailPilha.compare("tail") == 0) {
		this->setTailPilha(true);
	} else {
		this->setTailPilha(false);
	}
	this->setConcatenar(concatenar);
	this->setConcatenarPilha(concatenarPilha);
	this->setProximoEstado(proximoEstado);
}

void Saida::setTail(bool tail) {
	this->tail = tail;
}

void Saida::setConcatenar(string concatenar) {
	this->concatenar = concatenar;
}

void Saida::setProximoEstado(string proximoEstado) {
	this->proximoEstado = proximoEstado;
}

void Saida::setTailPilha(bool tailPilha) {
	this->tailPilha = tailPilha;
}
void Saida::setConcatenarPilha(string concatenarPilha) {
	this->concatenarPilha = concatenarPilha;
}

bool Saida::isTailPilha() const {
	return (this->tailPilha);
}

string Saida::getConcatenarPilha() const {
	return (this->concatenarPilha);
}

bool Saida::isTail() const {
	return (this->tail);
}

string Saida::getConcatenar() const {
	return (this->concatenar);
}

string Saida::getProximoEstado() const {
	return (this->proximoEstado);
}

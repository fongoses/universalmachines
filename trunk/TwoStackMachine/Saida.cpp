#include "Saida.h"

Saida::Saida() {
}

Saida::~Saida() {
}

Saida::Saida(string tail, string tailPilha, string tailPilha2,
		string concatenar, string concatenarPilha, string concatenarPilha2,
		string proximoEstado) {

	this->concatenarStack = vector<string>(2);
	this->tailStack = vector<bool>(2);

	if (tail.compare("tail") == 0) {
		this->setTail(true);
	} else {
		this->setTail(false);
	}

	if (tailPilha.compare("tail") == 0) {
		this->setTailStack(0, true);
	} else {
		this->setTailStack(0, false);
	}

	if (tailPilha2.compare("tail") == 0) {
		this->setTailStack(1, true);
	} else {
		this->setTailStack(1, false);
	}

	this->setConcatenar(concatenar);
	this->setConcatenarStack(0, concatenarPilha);
	this->setConcatenarStack(1,concatenarPilha2);
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

void Saida::setTailStack(int stack, bool tailStack) {
	this->tailStack[stack] = tailStack;
}
void Saida::setConcatenarStack(int stack, string concatenarStack) {
	this->concatenarStack[stack] = concatenarStack;
}

bool Saida::isTailStack(int stack) const {
	return (this->tailStack[stack]);
}
string Saida::getConcatenarStack(int stack) const {
	return (this->concatenarStack[stack]);
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

bool operator==(const Saida& s1, const Saida& s2) {
	return ((s1.tail==s2.tail)&&(s1.concatenar==s2.concatenar)
			&&(s1.proximoEstado ==s2.proximoEstado)&&(s1.tailStack[0]
			==s2.tailStack[0])&&(s1.concatenarStack[0]==s2.concatenarStack[0]));
}


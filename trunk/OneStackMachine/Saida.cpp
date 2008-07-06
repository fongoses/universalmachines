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
		this->setTailStack(0,true);
	} else {
		this->setTailStack(0,false);
	}
	this->setConcatenar(concatenar);
	this->setConcatenarStack(0,concatenarPilha);
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


void Saida::setTailStack(int stack ,bool tailStack){
	this->tailStack[stack] = tailStack;
}
void Saida::setConcatenarStack(int stack ,string concatenarStack){
	this->concatenarStack[stack] = concatenarStack;
}

bool Saida::isTailStack(int stack)const{
	return(this->tailStack[stack]);
}
string Saida::getConcatenarStack(int stack)const{
	return(this->concatenarStack[stack]);
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

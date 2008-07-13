#include "Saida.h"

Saida::Saida() {
}

Saida::~Saida() {
}

Saida::Saida(string tail, string concatenar, string proximoEstado){
	if(tail.compare("tail") == 0){
		this->setTail(true);
	}else{
		this->setTail(false);
	}
	this->setConcatenar(concatenar);
	this->setProximoEstado(proximoEstado);
}

void Saida::setTail(bool tail){
	this->tail = tail;
}

void Saida::setConcatenar(string concatenar){
	this->concatenar = concatenar;
}

void Saida::setProximoEstado(string proximoEstado){
	this->proximoEstado = proximoEstado;
}

bool Saida::isTail(){
	return(this->tail);
}

string Saida::getConcatenar() const{
	return(this->concatenar);
}

string Saida::getProximoEstado()const{
	return(this->proximoEstado);
}

bool operator==(const Saida& s1, const Saida& s2) {
	return (s1.tail==s2.tail)&&(s1.concatenar==s2.concatenar)
			&&(s1.proximoEstado ==s2.proximoEstado);
}


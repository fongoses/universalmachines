#include "Entrada.h"

Entrada::Entrada() {
}

Entrada::~Entrada() {
}

Entrada::Entrada(string estado, string head, string headStackOne) {
	this->setEstado(estado);
	this->setHead(head);
	this->setHeadStack(0,headStackOne);
}

void Entrada::setHeadStack(int stack,string headStackOne){
	this->headStack[stack] = headStackOne;
}

string Entrada::getHeadStack(int stack) const{
	return(this->headStack[stack]);
}

void Entrada::setEstado(string estado) {
	this->estado = estado;
}

void Entrada::setHead(string head) {
	this->head = head;
}

string Entrada::getEstado() const {
	return (this->estado);
}

string Entrada::getHead() const {
	return (this->head);
}

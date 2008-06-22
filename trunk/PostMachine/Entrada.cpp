#include "Entrada.h"

Entrada::Entrada() {
}

Entrada::~Entrada() {
}

Entrada::Entrada(string estado,string head) {
	this->setEstado(estado);
	this->setHead(head);
}

void Entrada::setEstado(string estado){
	this->estado = estado;
}

void Entrada::setHead(string head){
	this->head = head;
}

string Entrada::getEstado() const{
	return(this->estado);
}

string Entrada::getHead()const{
	return(this->head);
}

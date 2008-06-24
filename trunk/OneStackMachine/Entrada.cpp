#include "Entrada.h"

Entrada::Entrada() {
}

Entrada::~Entrada() {
}

void Entrada::setHeadPilha(string headPilha){
	this->headPilha = headPilha;
}

string Entrada::getHeadPilha() const{
	return(this->headPilha);
}

Entrada::Entrada(string estado,string head, string headPilha) {
	this->setEstado(estado);
	this->setHead(head);
	this->setHeadPilha(headPilha);
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

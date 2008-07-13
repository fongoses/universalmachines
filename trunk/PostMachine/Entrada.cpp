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

bool operator==(const Entrada& e1, const Entrada& e2) {
	return (e1.estado==e2.estado)&&(e1.head==e2.head);
}

bool operator<(const Entrada& e1, const Entrada& e2) {
	if (e1.estado<e2.estado)
		return true;
	else {
		if ((e1.estado==e2.estado)&&(e1.head<e2.head))
			return true;
	}
	return false;

}

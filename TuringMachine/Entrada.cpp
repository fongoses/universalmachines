#include "Entrada.h"

Entrada::Entrada() {

}

Entrada::Entrada(string estado, string simbolo) {
	this->setEstado(estado);
	this->setSimbolo(simbolo);
}

void Entrada::setEstado(string estado) {
	this->estado = estado;
}

void Entrada::setSimbolo(string simbolo) {
	this->simbolo = simbolo;
}

string Entrada::getEstado() const {
	return (this->estado);
}
string Entrada::getSimbolo() const {
	return (this->simbolo);
}

bool operator==(const Entrada& e1, const Entrada& e2) {
	return (e1.estado==e2.estado)&&(e1.simbolo==e2.simbolo);
}

bool operator<(const Entrada& e1, const Entrada& e2) {
	if (e1.estado<e2.estado)
		return true;
	else {
		if ((e1.estado==e2.estado)&&(e1.simbolo<e2.simbolo))
			return true;
	}
	return false;

}
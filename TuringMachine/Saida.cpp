#include "Saida.h"

Saida::Saida() {

}

Saida::Saida(string estado, string simbolo, string movimento) {
	this->estado = estado;
	this->simbolo = simbolo;
	this->movimento = movimento;
}

void Saida::setEstado(string estado) {
	this->estado = estado;
}

void Saida::setSimbolo(string simbolo) {
	this->simbolo = simbolo;
	if (this->simbolo.compare("R") == 0) {
		this->typeMove = RIGHT;
	} else if (this->simbolo.compare("L") == 0) {
		this->typeMove = LEFT;
	} else if (this->simbolo.compare("S") == 0) {
		this->typeMove = STOP;
	}
}

void Saida::setMovimento(string movimento) {
	this->movimento = movimento;
}

string Saida::getEstado() const {
	return (this->estado);
}

string Saida::getSimbolo() const {
	return (this->simbolo);
}

string Saida::getMovimento() const {
	if (this->movimento.compare("L") == 0) {
		return ("LEFT");
	}
	if (this->movimento.compare("R") == 0) {
		return ("RIGHT");
	}
	if (this->movimento.compare("S") == 0) {
		return ("STOP");
	}
}

int Saida::move() {
	if (this->movimento.compare("L") == 0) {
		return (-1);
	}
	if (this->movimento.compare("R") == 0) {
		return (1);
	}
	if (this->movimento.compare("S") == 0) {
		return (0);
	}
}

TypeMove Saida::getTypeMove() const {
	return (this->typeMove);
}

bool operator==(const Saida& s1, const Saida& s2) {
	return (s1.estado==s2.estado)&&(s1.simbolo==s2.simbolo)&&(s1.movimento
			==s2.movimento);
}


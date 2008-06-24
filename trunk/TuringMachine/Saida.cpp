#include "Saida.h"

Saida::Saida() {

}

Saida::Saida(string estado, string simbolo, string movimento) {
	this->estado = estado;
	this->simbolo = simbolo;
	this->movimento = movimento;
}

int Saida::move() {
	if (movimento=="L")
		return -1;
	if (movimento=="R")
		return 1;
	if (movimento=="P")
		return 0;
	return 2;
}

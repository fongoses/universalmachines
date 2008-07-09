#include "Entrada.h"

Entrada::Entrada() {
}

Entrada::~Entrada() {
}

Entrada::Entrada(string estado, string head, string headStackOne) {
	this->setEstado(estado);
	this->setHead(head);
	this->headStack = vector<string>(1);
	this->setHeadStack(0, headStackOne);
}

void Entrada::setHeadStack(int stack, string headStackOne) {
	this->headStack[stack] = headStackOne;
}

string Entrada::getHeadStack(int stack) const {
	return (this->headStack[stack]);
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
bool operator==(const Entrada& e1, const Entrada& e2) {
	return ((e1.estado==e2.estado)&&(e1.head==e2.head)&&(e1.headStack[0]
			==e2.headStack[0]));
}

bool operator<(const Entrada& e1, const Entrada& e2) {
	if (e1.estado<e2.estado)
	return true;
	else {
		if ((e1.estado==e2.estado)&&(e1.head<e2.head)&&(e1.headStack[0]
						==e2.headStack[0]))
		return true;
		if ((e1.estado==e2.estado)&&(e1.head==e2.head)&&(e1.headStack[0]
						<e2.headStack[0]))
		return true;

	}
	return false;
}

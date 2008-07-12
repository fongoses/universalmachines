#include "Alfabeto.h"

Alfabeto::Alfabeto() {
}

Alfabeto::~Alfabeto() {
}

void Alfabeto::setAlfabeto(vector<string> alfa) {
	this->alfabeto = alfa;
}

bool Alfabeto::isCaracterDoAlfabeto(vector<string> palavra) {
	vector<string>::iterator it;
	vector<string>::iterator it2;
	bool aux = true;
	for (it = palavra.begin(); it < palavra.end(); it++) {
		aux = false;
		for (it2 = this->alfabeto.begin(); it2 < this->alfabeto.end(); it2++) {
			if((*it2).compare(*it) == 0){
				aux = true;
			}
		}
		if(!aux){
			return(false);
		}
	}
	return(true);
}

string Alfabeto::getAlfabeto() {

	vector<string>::iterator it;
	string word = "\"{";

	for (it = this->alfabeto.begin(); it < this->alfabeto.end(); it++) {
		word += *it + ",";
	}

	return (word += "}\"");

}

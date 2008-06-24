#include "Cadeia.h"

Cadeia::Cadeia() {
}

Cadeia::~Cadeia() {
}

void Cadeia::setPalavra(vector<string> str) {
	vector<string>::iterator it;
	if (str.size()!= 0) {
		for (it = str.begin(); it < str.end(); it++) {
			this->palavra.push_back(*it);
		}
	}
}

list<string> Cadeia::getPalavra() {
	return (this->palavra);
}

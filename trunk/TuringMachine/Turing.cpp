#include "Turing.h"

Turing::Turing() {
	posicao = 0;
	producoes = "";

}

bool Turing::executa() {
	Entrada entrada(estado, fita[posicao]);
	if (delta.find(entrada) != delta.end()) {
		Saida saida = delta[entrada];
		producoes += imprimeRegra(entrada, saida);
		estado = saida.estado;
		fita[posicao] = saida.simbolo;
		posicao += saida.move();
		if (posicao== (int)fita.size()) {
			fita.push_back("B");
		}
	} else {
		return false;
	}
	return true;
}

void Turing::imprimeFita() {
	cout << "(" << estado << ")   ";
	for (int i=0; i<(int)fita.size(); i++) {
		if (i==posicao)
			cout << "[" << fita[i] << "] ";
		else
			cout << fita[i] << " ";
	}
	cout << endl;
}

string Turing::imprimeRegra(Entrada entrada, Saida saida) {
	string aux = "";
	aux = "delta(" + entrada.estado + ", " + entrada.simbolo + ") = ";
	aux += "(" + saida.estado + ", " + saida.simbolo + ", " + saida.movimento
			+ ") \n";
	return aux;
}

bool Turing::final() {
	if (finais.find(estado)!=finais.end())
		return true;
	else
		return false;
}

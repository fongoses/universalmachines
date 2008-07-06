#include "OneStack.h"

OneStack::OneStack() {
}

OneStack::~OneStack() {
}

void OneStack::tail(typeQueue tipo) {
	if (tipo == FILA) {
		if (!this->isEmpty(tipo)) {
			this->palavraEntrada.pop_front();
		}
	} else if (tipo == STACKONE) {
		if (!this->isEmpty(tipo)) {
			this->pilhaOne.pop_front();
		}
	}

}

string OneStack::head(typeQueue tipo) {
	string cabeca = "";
	if (tipo == FILA) {
		if (!this->isEmpty(tipo)) {
			cabeca = this->palavraEntrada.front();
		}
	}else if(tipo == STACKONE){
		if (!this->isEmpty(tipo)) {
			cabeca = this->pilhaOne.front();
		}
	}
	return (cabeca);
}

void OneStack::concatenarBegin(string caracter, typeQueue tipo) {
	if (tipo == FILA) {
		this->palavraEntrada.push_front(caracter);
	} else if (tipo == STACKONE) {
		this->pilhaOne.push_front(caracter);
	}

}

void OneStack::concatenarEnd(string caracter, typeQueue tipo) {
	if (tipo == FILA) {
		this->palavraEntrada.push_back(caracter);
	} else if (tipo == STACKONE) {
		this->pilhaOne.push_back(caracter);
	}
}

void OneStack::setPalavraEntrada(list<string> palavraEntrada) {
	this->palavraEntrada = palavraEntrada;
}

bool OneStack::isEmpty(typeQueue tipo) {
	if (tipo == FILA) {
		return (this->palavraEntrada.empty());
	} else if (tipo == STACKONE) {
		return (this->pilhaOne.empty());
	}
}


void OneStack::insertDados(Entrada in, Saida out) {
	this->delta.insert(pair<Entrada, Saida>(in, out) );
}

bool OneStack::executar() {
/*	map<Entrada,Saida>::iterator it;
	Entrada entrada("START", "~","~");
	string cabeca = "";
	string nextState = "";
	while (true) {
		this->showPalavraEntrada();

		Saida saida = this->delta[entrada];

		cout << "Estado Atual :" << entrada.getEstado() <<"    Cabeca: "
				<< entrada.getHead()<<endl;

		cout << "Concatenacao:" << saida.getConcatenar()
				<<"     Proximo Estado: " << saida.getProximoEstado()<<endl;

		if (saida.isTail()) {
			//cabeca = this->head();
			this->tail();
		}
		if (saida.getConcatenar().compare("~") != 0) {
			this->concatenarEnd(saida.getConcatenar());
		}
		if (saida.getProximoEstado().compare("ACCEPT") == 0) {
			return true;
		} else if (saida.getProximoEstado().compare("REJECT") == 0) {
			return false;
		} else {
			nextState = saida.getProximoEstado();
			cout << "nextstate " << nextState <<endl<<endl;
		}
		cabeca = this->head();
		if (cabeca.compare("") == 0) {
			cabeca = "@";
		}
		entrada = Entrada(nextState, cabeca);
		cabeca = "";*/
	//}
	return false;
}
void OneStack::showPalavraEntrada() {
	list<string>::iterator it;
	cout<<"Resultado Parcial : ";
	if (!this->palavraEntrada.empty()) {
		for (it = this->palavraEntrada.begin(); it
				!= this->palavraEntrada.end(); it++) {
			cout << *it;
		}
	} else {
		cout << " vazia";
	}
	cout << endl;
}

void OneStack::showDelta() {
	map<Entrada,Saida>::iterator it;
	cout << "mymap contains:\n";
	for (it = this->delta.begin() ; it != this->delta.end(); it++)
		cout << "estado: " <<(*it).first.getEstado() << "   head: "<< (*it).first.getHead() << " => concatenar" << (*it).second.getConcatenar()<<"   proximo: "<< (*it).second.getProximoEstado()<< endl;
}

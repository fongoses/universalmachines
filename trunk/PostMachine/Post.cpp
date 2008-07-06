#include "Post.h"

Post::Post() {
}

Post::~Post() {
}

void Post::tail() {
	if(!this->isEmpty()){
		this->palavraEntrada.pop_front();	
	}
}

string Post::head() {
	string cabeca = "";
	if (!this->isEmpty()) {
		cabeca = this->palavraEntrada.front();
	}
	return (cabeca);
}

void Post::concatenarBegin(string caracter) {
	this->palavraEntrada.push_front(caracter);
}

void Post::concatenarEnd(string caracter) {
	this->palavraEntrada.push_back(caracter);
}

void Post::setPalavraEntrada(list<string> palavraEntrada) {
	this->palavraEntrada = palavraEntrada;
}

bool Post::isEmpty() {
	return (this->palavraEntrada.empty());
}
void Post::insertDados(Entrada in, Saida out) {
	this->delta.insert(pair<Entrada, Saida>(in, out) );
	/*this->deltaEntrada.push_back(in);
	 this->deltaSaida.push_back(out);*/
}

bool Post::executar() {
	map<Entrada,Saida>::iterator it;
	Entrada entrada("START", "~");
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
		if(cabeca.compare("") == 0){
			cabeca = "@";
		}
		entrada = Entrada(nextState, cabeca);
		cabeca = "";
	}
	return false;
}
void Post::showPalavraEntrada() {
	list<string>::iterator it;
	cout<<"Resultado Parcial : ";
	if(!this->palavraEntrada.empty()){
		for (it = this->palavraEntrada.begin(); it != this->palavraEntrada.end(); it++){
			cout << *it;			
		}
	}else{
		cout << " vazia";
	}
	cout << endl;
}

void Post::showDelta() {
	map<Entrada,Saida>::iterator it;
	cout << "Funcao Programa da Maquina de POST:\n";
	for (it = this->delta.begin() ; it != this->delta.end(); it++)
		cout << "estado: " <<(*it).first.getEstado() << "   head: "<< (*it).first.getHead() << " => concatenar" << (*it).second.getConcatenar()<<"   proximo: "<< (*it).second.getProximoEstado()<< endl;
}

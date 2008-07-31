#include "OneStack.h"

OneStack::OneStack() {
	this->fileOut = NULL;
	this->loop = 0;
}

OneStack::~OneStack() {
}
void OneStack::setFileOut(Arquivo* fileOut) {
	this->fileOut = fileOut;
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
void OneStack::setLoop(char* loop) {
	string looping = (string)loop;

	stringstream stm;
	stm.str(looping);
	stm >> this->loop;
}

int OneStack::getLoop() {
	return (this->loop);
}

string OneStack::head(typeQueue tipo) {
	string cabeca = "";
	if (tipo == FILA) {
		if (!this->isEmpty(tipo)) {
			cabeca = this->palavraEntrada.front();
		}
	} else if (tipo == STACKONE) {
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

string OneStack::executar() {
	map<Entrada,Saida>::iterator it;
	int tamanho = (int)this->delta.size();

	Entrada entrada("START", "~", "~");

	/*
	 * variaveis auxiliares para ajudar na maquina
	 */
	string cabeca = "";
	string cabecaPilha = "";
	string nextState = "";
	bool isFila = false;
	bool isStackOne = false;

	int looping = this->getLoop();

	while (looping >= 0) {
		try {
			isFila = false;
			isStackOne = false;

			this->showPalavraEntrada();
			this->showPilha(0);
			cout << endl;

			Saida saida("","","","","");

			it = this->delta.begin();

			/*
			 * faz a procura na map, 
			 * a funcao find nao estava funfando!!!!
			 */
			try {
				int i = 1;
				for (it = this->delta.begin(); it != this->delta.end(); it++ ) {
					if (((*it).first.getEstado().compare(entrada.getEstado())==0)&&((*it).first.getHead().compare(entrada.getHead())==0)&&((*it).first.getHeadStack(0).compare(entrada.getHeadStack(0))==0)) {
						saida = (*it).second;
						this->lookAhead(entrada,saida,&isStackOne,&isFila);
						break;
					} else if(i> tamanho) {
						this->fileOut->write("\n\nENTRANDA NAO EXISTENTE: \n\n");
						this->fileOut->write("ESTADO: "+entrada.getEstado()+"\n");
						this->fileOut->write("\nCABECA: "+entrada.getHead()+"\n");
						this->fileOut->write("\nCABECA PILHA: "+entrada.getHeadStack(0)+"\n");
						throw string("\nERRO NA PROCURA NA MAP");
					}
					i++;
				}

			} catch (string s) {
				this->fileOut->write(s+"\n");
				system("pause");
				exit(1);
			}

			this->fileOut->write("Estado Atual :" + entrada.getEstado() + "    Cabeca: "
					+ entrada.getHead() + "  CabecaPilha: "
					+ entrada.getHeadStack(0) + "\n");

			this->fileOut->write("Concatenacao:" + saida.getConcatenar()
					+ "  ConcatenacaoPilha: " + saida.getConcatenarStack(0)
					+ "     Proximo Estado: " + saida.getProximoEstado() + "\n\n");

			this->fileOut->write("---------------------------------------------------------------------------------- \n");

			if (saida.isTail()) {
				this->tail(FILA);
			}
			if (saida.isTailStack(0)) {
				this->tail(STACKONE);
			}
			if (saida.getConcatenar().compare("~") != 0) {
				this->concatenarEnd(saida.getConcatenar(), FILA);
			}
			if (saida.getConcatenarStack(0).compare("~") != 0) {
				this->concatenarBegin(saida.getConcatenarStack(0), STACKONE);
			}
			if (saida.getProximoEstado().compare("ACCEPT") == 0) {
				return ("\n\nA Maquina de uma Pilha ACEITOU a palavra: ");
			} else if (saida.getProximoEstado().compare("REJECT") == 0) {
				return ("\n\nA Maquina de uma Pilha REJEITOU a palavra : ");
			} else {
				nextState = saida.getProximoEstado();
			}

			if(isFila) {

				cabeca = this->head(FILA);
				cabecaPilha = "~";

			} else if(isStackOne) {

				cabecaPilha = this->head(STACKONE);
				cabeca = "~";
			}

			if (cabeca.compare("") == 0) {
				cabeca = "@";
			}
			if (cabecaPilha.compare("") == 0) {
				cabecaPilha = "@";
			}

			entrada = Entrada(nextState, cabeca, cabecaPilha);

			cabeca = "";
			cabecaPilha = "";
			looping--;
		} catch (...) {
			this->fileOut->write("ERRO DE EXECUCAO\n");
			system("pause");
			exit(1);
		}

	}
	return ("\n\nA maquina de 2 Pilhas entrou em LOOP (laco de \""
			+this->IntToString(this->loop) +"\" repeticoes) para a palavra: ");
}
void OneStack::lookAhead(Entrada entrada, Saida saida, bool *isStackOne,
		bool *isFila) {
	map<Entrada,Saida>::iterator it;
	int tamanho = (int)this->delta.size();
	try {
		int i = 1;
		for (it = this->delta.begin(); it != this->delta.end(); it++ ) {
			if (((*it).first.getEstado().compare(saida.getProximoEstado())==0)) {
				if(((*it).first.getHead().compare("~") == 0)&&((*it).first.getHeadStack(0).compare("~") != 0)) {
					*isStackOne = true;
				} else if(((*it).first.getHead().compare("~") != 0)&&((*it).first.getHeadStack(0).compare("~") == 0)) {
					*isFila = true;
				}
				break;
			} else if(i> tamanho) {
				this->fileOut->write("\n\nLOOK AHEAD FALHOU: \n\n");
				this->fileOut->write("ESTADO: " + entrada.getEstado()+"\n");
				this->fileOut->write("CABECA: " + entrada.getHead() + "\n");
				this->fileOut->write("CABECA PILHA: " + entrada.getHeadStack(0) + "\n");
				throw string("\nERRO NA PROCURA NA MAP");
			}
			i++;
		}

	} catch (string s) {
		this->fileOut->write(s+"\n");
		system("pause");
		exit(1);
	}
}
void OneStack::showPalavraEntrada() {
	list<string>::iterator it;
	this->fileOut->write("Resultado Parcial : ");
	string word = "";
	if (!this->palavraEntrada.empty()) {
		for (it = this->palavraEntrada.begin(); it
				!= this->palavraEntrada.end(); it++) {
			word += *it;
		}
		this->fileOut->write(word+"\n");
	} else {
		this->fileOut->write("vazia\n");
	}
}

void OneStack::showPilha(int stack) {
	if (stack == 0) {
		list<string>::iterator it;
		this->fileOut->write("Pilha: ");
		string word = "";
		if (!this->pilhaOne.empty()) {
			for (it = this->pilhaOne.begin(); it != this->pilhaOne.end(); it++) {
				word += *it;
			}
			this->fileOut->write(word+"\n");
		} else {
			this->fileOut->write("vazia\n");
		}
	}
}

void OneStack::showDelta() {
	map<Entrada,Saida>::iterator it;
	this->fileOut->write("Funcao Programa da Maquina de 1 PILHA:\n\n");
	for (it = this->delta.begin(); it != this->delta.end(); it++) {
		this->fileOut->write("estado: " + (*it).first.getEstado()+ "   head: " + (*it).first.getHead() + "   headPilha: " + (*it).first.getHeadStack(0) + "    =>     concatenar: " + (*it).second.getConcatenar()+ "   concatenar Pilha:" + (*it).second.getConcatenarStack(0)+"   proximo: " +(*it).second.getProximoEstado()+"\n");

	}
	this->fileOut->write("---------------------------------------------------------------------------------- \n");
	this->fileOut->write("\n\n\n");
}

string OneStack::IntToString(int num) {
	stringstream out;
	out << num;
	return (out.str());
}


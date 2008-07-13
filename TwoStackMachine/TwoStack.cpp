#include "TwoStack.h"

TwoStack::TwoStack() {
	this->fileOut = NULL;
}

TwoStack::~TwoStack() {
}

void TwoStack::setFileOut(Arquivo* fileOut) {
	this->fileOut = fileOut;
}
void TwoStack::tail(typeQueue tipo) {
	if (tipo == FILA) {
		if (!this->isEmpty(tipo)) {
			this->palavraEntrada.pop_front();
		}
	} else if (tipo == STACKONE) {
		if (!this->isEmpty(tipo)) {
			this->pilhaOne.pop_front();
		}
	} else if (tipo == STACKTWO) {
		if (!this->isEmpty(tipo)) {
			this->pilhaTwo.pop_front();
		}
	}

}

string TwoStack::head(typeQueue tipo) {
	string cabeca = "";
	if (tipo == FILA) {
		if (!this->isEmpty(tipo)) {
			cabeca = this->palavraEntrada.front();
		}
	} else if (tipo == STACKONE) {
		if (!this->isEmpty(tipo)) {
			cabeca = this->pilhaOne.front();
		}
	} else if (tipo == STACKTWO) {
		if (!this->isEmpty(tipo)) {
			cabeca = this->pilhaTwo.front();
		}
	}
	return (cabeca);
}

void TwoStack::concatenarBegin(string caracter, typeQueue tipo) {
	if (tipo == FILA) {
		this->palavraEntrada.push_front(caracter);
	} else if (tipo == STACKONE) {
		this->pilhaOne.push_front(caracter);
	} else if (tipo == STACKTWO) {
		this->pilhaTwo.push_front(caracter);
	}

}

void TwoStack::concatenarEnd(string caracter, typeQueue tipo) {
	if (tipo == FILA) {
		this->palavraEntrada.push_back(caracter);
	} else if (tipo == STACKONE) {
		this->pilhaOne.push_back(caracter);
	} else if (tipo == STACKONE) {
		this->pilhaTwo.push_back(caracter);
	}
}

void TwoStack::setPalavraEntrada(list<string> palavraEntrada) {
	this->palavraEntrada = palavraEntrada;
}

bool TwoStack::isEmpty(typeQueue tipo) {
	if (tipo == FILA) {
		return (this->palavraEntrada.empty());
	} else if (tipo == STACKONE) {
		return (this->pilhaOne.empty());
	} else if (tipo == STACKTWO) {
		return (this->pilhaTwo.empty());
	}
}

void TwoStack::insertDados(Entrada in, Saida out) {
	this->delta.insert(pair<Entrada, Saida>(in, out) );
}

bool TwoStack::executar() {
	map<Entrada,Saida>::iterator it;
	int tamanho = (int)this->delta.size();

	Entrada entrada("START", "~", "~", "~");

	/*
	 * variaveis auxiliares para ajudar na maquina
	 */
	string cabeca = "";
	string cabecaPilha = "";
	string cabecaPilha2 = "";
	string nextState = "";
	bool isFila = false;
	bool isStackOne = false;
	bool isStackTwo = false;

	while (true) {
		try {
			isFila = false;
			isStackOne = false;
			isStackTwo = false;

			this->showPalavraEntrada();
			this->showPilha(0,this->pilhaOne);
			this->showPilha(1,this->pilhaTwo);

			Saida saida("","","","","","","");

			it = this->delta.begin();

			/*
			 * faz a procura na map, 
			 * a funcao find nao estava funfando!!!!
			 */
			try {
				int i = 1;
				for (it = this->delta.begin(); it != this->delta.end(); it++ ) {
					if (((*it).first.getEstado().compare(entrada.getEstado()) == 0)
							&&((*it).first.getHead().compare(entrada.getHead()) == 0)
							&&((*it).first.getHeadStack(0).compare(entrada.getHeadStack(0)) == 0)
							&&((*it).first.getHeadStack(1).compare(entrada.getHeadStack(1)) == 0)) {
						saida = (*it).second;
						this->lookAhead(entrada,saida,&isFila,&isStackOne,&isStackTwo);
						break;
					} else if(i> tamanho) {
						this->fileOut->write("\n\nENTRANDA NAO EXISTENTE: \n\n");
						this->fileOut->write("ESTADO: "+entrada.getEstado()+"\n");
						this->fileOut->write("\nCABECA: "+entrada.getHead()+"\n");
						this->fileOut->write("\nCABECA PILHA 1: "+entrada.getHeadStack(0)+"\n");
						this->fileOut->write("\nCABECA PILHA 2: "+entrada.getHeadStack(1)+"\n");
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
					+ entrada.getHead() + "  CabecaPilha 1: "
					+ entrada.getHeadStack(0) +
					"  CabecaPilha 2: "+ entrada.getHeadStack(1) +"\n");

			this->fileOut->write("Concatenacao:" + saida.getConcatenar()
					+ "  ConcatenacaoPilha 1: " + saida.getConcatenarStack(0)
					+ "  ConcatenacaoPilha 2: " + saida.getConcatenarStack(1)
					+ "     Proximo Estado: " + saida.getProximoEstado() + "\n\n");

			this->fileOut->write("---------------------------------------------------------------------------------- \n");

			if (saida.isTail()) {
				this->tail(FILA);
			}
			if (saida.isTailStack(0)) {
				this->tail(STACKONE);
			}
			if(saida.isTailStack(1)) {
				this->tail(STACKTWO);
			}
			if (saida.getConcatenar().compare("~") != 0) {
				this->concatenarEnd(saida.getConcatenar(), FILA);
			}
			if (saida.getConcatenarStack(0).compare("~") != 0) {
				this->concatenarBegin(saida.getConcatenarStack(0), STACKONE);
			}
			if (saida.getConcatenarStack(1).compare("~") != 0) {
				this->concatenarBegin(saida.getConcatenarStack(1), STACKTWO);
			}
			if (saida.getProximoEstado().compare("ACCEPT") == 0) {
				return true;
			} else if (saida.getProximoEstado().compare("REJECT") == 0) {
				return false;
			} else {
				nextState = saida.getProximoEstado();
			}

			if(isFila) {
				cabeca = this->head(FILA);
				cabecaPilha = "~";
				cabecaPilha2 = "~";

			} else if(isStackOne) {
				cabecaPilha = this->head(STACKONE);
				cabecaPilha2 = "~";
				cabeca = "~";
			} else if(isStackTwo) {
				cabecaPilha2 = this->head(STACKTWO);
				cabecaPilha = "~";
				cabeca = "~";
			}

			if (cabeca.compare("") == 0) {
				cabeca = "@";
			}
			if (cabecaPilha.compare("") == 0) {
				cabecaPilha = "@";
			}

			if (cabecaPilha2.compare("") == 0) {
				cabecaPilha2 = "@";
			}

			entrada = Entrada(nextState, cabeca, cabecaPilha,cabecaPilha2);

			cabeca = "";
			cabecaPilha = "";
			cabecaPilha2 = "";
		} catch (...) {
			this->fileOut->write("ERRO DE EXECUCAO\n");
			system("pause");
			exit(1);
		}

	}
	return false;
}
void TwoStack::lookAhead(Entrada entrada, Saida saida, bool *isFila,
		bool *isStackOne, bool *isStackTwo) {
	map<Entrada,Saida>::iterator it;
	int tamanho = (int)this->delta.size();
	try {
		int i = 1;
		for (it = this->delta.begin(); it != this->delta.end(); it++ ) {
			if (((*it).first.getEstado().compare(saida.getProximoEstado())==0)) {
				if(((*it).first.getHead().compare("~") == 0)&&((*it).first.getHeadStack(0).compare("~") != 0)&&((*it).first.getHeadStack(1).compare("~") == 0)) {
					*isStackOne = true;
				} else if(((*it).first.getHead().compare("~") != 0)&&((*it).first.getHeadStack(0).compare("~") == 0) && ((*it).first.getHeadStack(1).compare("~") == 0)) {
					*isFila = true;
				} else if(((*it).first.getHead().compare("~") == 0)&&((*it).first.getHeadStack(0).compare("~") == 0)&&((*it).first.getHeadStack(1).compare("~") != 0)) {
					*isStackTwo = true;
				} 
				break;
			} else if(i> tamanho) {
				this->fileOut->write("\n\nLOOK AHEAD FALHOU: \n\n");
				this->fileOut->write("ESTADO: " + entrada.getEstado()+"\n");
				this->fileOut->write("CABECA: " + entrada.getHead() + "\n");
				this->fileOut->write("CABECA PILHA 1: " + entrada.getHeadStack(0) + "\n");
				this->fileOut->write("CABECA PILHA 2: " + entrada.getHeadStack(1) + "\n");
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
void TwoStack::showPalavraEntrada() {
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

void TwoStack::showPilha(int stack, list<string> pilha) {
	list<string>::iterator it;
	string word = "";
	this->fileOut->write("Pilha"+this->IntToString(++stack)+": ");
	if (!pilha.empty()) {
		for (it = pilha.begin(); it != pilha.end(); it++) {
			word += *it;
		}
		this->fileOut->write(word+"\n");
	} else {
		this->fileOut->write("vazia\n");
	}
}

void TwoStack::showDelta() {
	map<Entrada,Saida>::iterator it;
	this->fileOut->write("Funcao Programa da Maquina de 2 PILHAS:\n\n");
	for (it = this->delta.begin(); it != this->delta.end(); it++) {
		this->fileOut->write("estado: " + (*it).first.getEstado()
				+ "   head: " + (*it).first.getHead()
				+ "   headPilha: " + (*it).first.getHeadStack(0) 
				+ "    =>     concatenar: " + (*it).second.getConcatenar()
				+ "   concatenar Pilha 1:" + (*it).second.getConcatenarStack(0)
				+ "   concatenar Pilha 2:" + (*it).second.getConcatenarStack(1)
				+"   proximo: " +(*it).second.getProximoEstado()+"\n");

	}
	this->fileOut->write("---------------------------------------------------------------------------------- \n");
	this->fileOut->write("\n\n\n");
}
string TwoStack::IntToString(int num) {
	stringstream out;
	out << num;
	return (out.str());
}

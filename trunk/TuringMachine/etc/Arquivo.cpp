#include "Arquivo.h"

/* @resume:construtor */
Arquivo::Arquivo() {
}

void Arquivo::setEnd(char *enderecoArquivo) {
	this->enderecoArquivo = enderecoArquivo;
}

string Arquivo::getEnd() const {
	return ((string)this->enderecoArquivo);
}
/* @resume:destrutor */
Arquivo::~Arquivo() {
}

/* 
 * @resume:funcao para abrir o arquivo 
 * @param: ios_base::openmode mode: modo de abertura
 */
void Arquivo::abrir(ios_base::openmode mode) {
	this->file.open(this->enderecoArquivo, mode);
}

/* 
 * @resume:funcao para fechar o arquivo 
 */
void Arquivo::fechar() {
	this->file.close();
}

/* 
 * @resume:funcao escrever no arquivo
 * @param: string line: string que contem
 */
void Arquivo::write(string line) {
	this->file << line;
}

/* 
 * @resume:funcao ler do arquivo
 * @return: linha do arquivo
 */
std::string Arquivo::getLinha() {
	std::string line;
	getline(this->file, line);
	return (line);
}

/* 
 * @resume:verificar se eh fim do arquivo
 * @return:
 * 		   True: se for fim;
 * 		   False: se nao
 */
bool Arquivo::isTheEnd() {
	return (this->file.eof());
}

/* 
 * @resume:verificar se o arquivo esta aberto
 * @return:
 * 		   True: se aberto;
 * 		   False: se nao
 */
bool Arquivo::isOpen() {
	return (this->file.is_open());
}

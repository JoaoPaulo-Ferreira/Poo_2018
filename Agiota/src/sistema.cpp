#include "sistema.h"

Sistema::Sistema(){}

Sistema::Sistema(int grana){
	granaTotal = grana;
}

void Sistema::Tr_add(std::string key, std::string value){
	transacoes.add(key, Transacao(key, value,indexTR++));
}
void Sistema::Cli_add(std::string key, std::string name){
	clientes.add(key, Cliente(key, name));
}

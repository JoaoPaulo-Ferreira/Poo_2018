#include "cliente.h"

Cliente::Cliente(){}

Cliente::Cliente(std::string id, std::string name, int divida = 0){
	Client_ID=id;
	Client_nome=name;
	dividaAtual=divida;
}

Cliente::Cliente(std::string id, std::string name){
	Client_ID=id;
	Client_nome=name;
	dividaAtual = 0;
}

std::string Cliente::toString(){
	std::stringstream out;
	out << Client_ID << ":" << Client_nome << ":" << dividaAtual;
	return out.str(); 
}
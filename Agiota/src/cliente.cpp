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
}

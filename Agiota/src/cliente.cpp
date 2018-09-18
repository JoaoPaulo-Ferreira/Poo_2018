#include "cliente.h"

Cliente::Cliente(){}

Cliente::Cliente(std::string id, std::string name, int divida = 0){
	cID=id;
	nome=name;
	dividaAtual=divida;
}

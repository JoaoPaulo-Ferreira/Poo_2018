#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <sstream>
class Cliente{
	public:
	std::string Client_ID;
	std::string Client_nome;
	int dividaAtual;

	Cliente();
	Cliente(std::string, std::string , int );
	Cliente(std::string, std::string);
	std::string toString();
};
#endif //SISTEMA_H
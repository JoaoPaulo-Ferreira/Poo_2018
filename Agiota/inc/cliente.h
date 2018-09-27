#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

class Cliente{
		std::string Client_ID;
		std::string Client_nome;
		int dividaAtual;
public:
	Cliente();
	Cliente(std::string, std::string , int );
	Cliente(std::string, std::string);
};
#endif //SISTEMA_H
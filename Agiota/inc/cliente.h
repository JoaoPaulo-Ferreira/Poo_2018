#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

class Cliente{
		std::string cID;
		std::string nome;
		int dividaAtual;
public:
	Cliente();
	Cliente(std::string, std::string , int );
};

#endif // CLIENTE_H

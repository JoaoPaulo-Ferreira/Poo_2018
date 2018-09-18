#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <iostream>

class Transacao{
	int tID;
	std::string clienteID;
public:
	Transacao();
	Transacao(int, std::string);
};

#endif // TRANSACAO_H

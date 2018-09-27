#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <iostream>

class Transacao{
	std::string Transacao_ID;
	std::string Client_ID;
	int index = 0;
public:
	Transacao();
	Transacao(std::string, std::string, int);
};
#endif //TRANSACAO_H
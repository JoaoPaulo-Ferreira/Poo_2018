#ifndef TRANSACAO_H
#define TRANSACAO_H

#include <iostream>
#include <sstream>
#include <cstdlib>

class Transacao{
	public:
	std::string Client_ID;
	int value;
	int index = 0;
	Transacao();
	Transacao(std::string, std::string, int);
	std::string toString();
};
#endif //TRANSACAO_H
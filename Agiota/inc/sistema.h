#ifndef SISTEMA_H
#define SISTEMA_H

#include "cliente.h"
#include "transacao.h"
#include <vector>

class Sistema{
	int granaTotal;
	std::vector<Cliente> clientes;
	std::vector<Transacao> transacoes; 	
public:
	Sistema();
	Sistema(int);	
};

#endif // SISTEMA_H

#ifndef SISTEMA_H
#define SISTEMA_H

#include "cliente.h"
#include "transacao.h"
#include "rep.h"
#include <map>

class Sistema{
	int granaTotal;
	int indexTR = 0;
	Rep<Cliente> clientes;
	Rep<Transacao> transacoes; 	
public:
	Sistema();
	Sistema(int);	
	void Tr_add(std::string , std::string );
	void Cli_add(std::string,std::string);
};

#endif // SISTEMA_H
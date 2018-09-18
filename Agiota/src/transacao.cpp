#include "transacao.h"

Transacao::Transacao(){}

Transacao::Transacao(int id, std::string cID){
	tID = id;
	clienteID=cID;
}

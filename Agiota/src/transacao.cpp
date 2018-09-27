
#include "transacao.h"

Transacao::Transacao(){}

Transacao::Transacao(std::string id, std::string cID, int _index){
	Transacao_ID = id;
	Client_ID=cID;
	index = _index;
}
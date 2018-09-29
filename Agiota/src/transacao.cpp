
#include "transacao.h"

Transacao::Transacao(){}

Transacao::Transacao(std::string cID, std::string _value, int _index){
	Client_ID = cID;
	value = std::atoi(_value.c_str());
	index = _index;
}

std::string Transacao::toString(){
	std::stringstream out;
	out << "id:" << index << " [" << Client_ID << " " << value << "]";
	return out.str();
}

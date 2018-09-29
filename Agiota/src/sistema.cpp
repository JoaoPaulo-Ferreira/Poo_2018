#include "sistema.h"

Sistema::Sistema(){}

Sistema::Sistema(int grana){
	granaTotal = grana;
}

void Sistema::TR_validate(std::string key, int value){
	// std::cout << "tr_validade " << value << "\n";
	if(clientes.exist(key)){
		auto cli = clientes.find(key);

		if(value >= 0){ // devolvendo grana
			// std::cout <<"pagando: " <<value << "devendo: " << cli->second.dividaAtual<< "\n";
			if(value <= -cli->second.dividaAtual){ // to devendo mais do que to pagando?
				
				cli->second.dividaAtual += value;
				granaTotal += value;
				return;
			}else // to pagando mais do que to devendo
				throw "fail: valor maior que divida";
		}else{ // tomando emprestado
			if(-value <= granaTotal){ // to pedindo menos do que o sistema tem?
				cli->second.dividaAtual += value;
				granaTotal += value;
				std::cout << "grana total = " << granaTotal << "\n";
				return;
			}
			else
				throw "fail: fundos insuficientes";
		}
	}else
		throw "fail: cliente bruno nao existe";
}
// void Sistema::Tr_add(std::string key, std::string value){
// 	transacoes.add(key, Transacao(key, value,indexTR++));
// }
// void Sistema::Cli_add(std::string key, std::string name){
// 	clientes.add(key, Cliente(key, name));
// }

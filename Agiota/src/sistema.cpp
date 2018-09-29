#include "sistema.h"

Sistema::Sistema(){}

Sistema::Sistema(int grana){
	granaTotal = grana;
}

void Sistema::TR_validate(std::string key, int value){
	if(clientes.exist(key)){
		auto cli = clientes.find(key);

		if(value >= 0){ // devolvendo grana
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
				return;
			}
			else
				throw "fail: fundos insuficientes";
		}
	}else
		throw "fail: cliente bruno nao existe";
}
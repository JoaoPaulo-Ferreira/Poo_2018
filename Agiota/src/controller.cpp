#include "controller.h"

#ifndef exp_enum
#define exp_enum
enum exp{
	C_EXIST = 0,
	T_EXIST,
	ADD_TYPE_INVALID
};
#endif



Controller::Controller(){}

std::string Controller::show_func(std::string comand){
	std::stringstream in(comand), out;
	std::string show_type;
	in >> show_type;
	if(show_type == "cli"){ //show all clients
		out << sistema.clientes.show_All();
	}else if(show_type == "tr"){
		out << sistema.transacoes.show_All();
	}else{
		out << sistema.transacoes.show(show_type);
	}
	return out.str();
}

void Controller::add_func(std::string comand){
	std::stringstream in(comand);
	std::string add_type, add_op1, add_op2;
	in >> add_type;
	in >> add_op1;
	getline(in, add_op2);
	add_op2.erase(add_op2.begin());
	if(add_type == "cli")
		sistema.clientes.add(add_op1, Cliente(add_op1, add_op2));
	else if(add_type == "tr"){
		int iDivida = std::atoi(add_op2.c_str());
		sistema.TR_validate(add_op1, iDivida);
		sistema.transacoes.add(std::to_string(sistema.indexTR), Transacao(add_op1, add_op2, sistema.indexTR));
		sistema.indexTR++;
	}
}


void Controller::mercenario(std::string clienteID){
	sistema.transacoes.del(clienteID);
	sistema.clientes.del(clienteID);
}

std::string Controller::shell(std::string line){
	std::stringstream in(line);
	std::stringstream out;
	std::string op;
	in >> op;
   	if(op == "help")
       	out << "init; add cli <id> <nome>; add tr <id> <valor>;"
		    << "show cli; show tr end" ;
	else if(op == "init"){
		int value;
		in >> value;
		sistema = Sistema(value);
		out << "done";
	}else if(op == "add"){
		std::string add_comand;
		getline(in, add_comand);
		add_func(add_comand);
		out << "done";
   	}else if(op == "show"){
		std::string show_type;
		getline(in, show_type);
		out << show_func(show_type);
    }else if(op == "matar"){
        std::string id;
		in >> id;
		mercenario(id);
	}
	return out.str();
}

void Controller::exec(){
	std::string line;
    while(true){
		getline(std::cin, line);
        if(line == "end")
			   	break;
		std::cout << line << std::endl;
		try{
		std::cout/* << "  " */<< shell(line) << std::endl;
		// std::cout << line << std::endl;
		}catch(const char *e){
			std::cout << e << std::endl;
 			// switch(e){
			// 	case C_EXIST:
			// 		std::cout << "id already exist" << std::endl;
			// 	break;
			// 	case T_EXIST:
			// 		std::cout << "transaction already exist" << std::endl;
			// 		break;
			// 	case ADD_TYPE_INVALID:
			// 		std::cout << "invalid add type" << std::endl;
			// 		break;
			// 	default:
			// 		std::cout << "default switch try catch" << std::endl;

			// }
		}
    }
}
#include "controller.h"

// #ifndef exp_enum
// #define exp_enum
// enum exp{
// 	C_EXIST = 0,
// 	T_EXIST,
// 	ADD_TYPE_INVALID
// };
// #endif
Controller::Controller(){}

void Controller::add_func(std::string comand){
	std::stringstream in(comand);
	std::string add_type, add_op1, add_op2;
	in >> add_type;
	in >> add_op1;
	getline(in, add_op2);
	if(add_type == "cli")
		sistema.Cli_add(add_op1, add_op2);			
	else if(add_type == "tr")
		sistema.Tr_add( add_op1, add_op2);
	// else
		// std::cout << "Oxi" << std::endl;//		throw ADD_TYPE_INVALID;
}

std::string Controller::shell(std::string line){
	std::stringstream in(line);
	std::stringstream out;
	std::string op;
	in >> op;
   	if(op == "help")
       	out << "init; add cli <id> <nome>; add tr <id> <valor>; end";
	else if(op == "init"){
		int value;
		in >> value;
		sistema = Sistema(value);
		// out << "sucesso";
	}else if(op == "add"){
		std::string add_comand;
		getline(in, add_comand);
		add_func(add_comand);
   	}/*else if(op == "add"){
    	string id, fone;
        in >> id >> fone;
        cont.add(Fone(id, fone));
    }else if(op == "rm"){
        string id;
		in >> id;
		cont.rm(id);
	}*/
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
		std::cout << "  " << shell(line) << std::endl;
		// std::cout << line << std::endl;
		}catch(int e){
 			switch(e){
				case exp::C_EXIST:
					std::cout << "client already exist" << std::endl;
				break;
				case exp::T_EXIST:
					std::cout << "transaction already exist" << std::endl;
					break;
				case exp::ADD_TYPE_INVALID:
					std::cout << "invalid add type" << std::endl;
					break;
				default:
					std::cout << "default switch try catch" << std::endl;

			}
		}
    }
}
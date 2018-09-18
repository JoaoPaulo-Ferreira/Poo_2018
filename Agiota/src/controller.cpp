#include "controller.h"

Controller::Controller(){}

std::string shell(std::string line){
	std::stringstream in(line);
	std::stringstream out;
	std::string op;
	in >> op;
   	if(op == "help")
       	out << "show; init _nome; add _id _fone; end";
	/*else if(op == "init"){
		string nome;
		in >> nome;
        cont = Contato(nome);
        out << "success";
	}else if(op == "show"){
        out << cont.toString();
   	}else if(op == "add"){
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

void exec(){
	std::string line;
    while(true){
		getline(std::cin, line);
        if(line == "end")
			   	break;
		std::cout << line << std::endl;
		std::cout << "  " << shell(line) << std::endl;
    }
}


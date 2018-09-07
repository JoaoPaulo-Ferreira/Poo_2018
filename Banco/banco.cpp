#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Operacao{
    int indice;
    string descricao;
	float valor;
	float saldo;

    Operacao(int _id, string desc, float val, float sal): indice(_id),descricao(desc), valor(val), saldo(sal){
    }

    string toString(){
        stringstream ss;
        ss << indice << ": " << setw(10) << descricao << ": " << setw(6) << valor << ": " << setw(6) << saldo;  
        return ss.str();
    }
};

struct Conta{
    int nextID;
	int numero;
	float saldo;
    vector<Operacao> extrato;

    Conta(int id = 0, float saldo = 0) : numero(id), nextID(0), saldo(saldo){
		pushOperation("abertura", 0, saldo);	
    }

	string toString(){
		stringstream s;
		s << "conta: " << numero << " saldo: " << saldo;
		return s.str();
	}

	void pushOperation(string label, float valor, float saldo){
		extrato.push_back(Operacao(nextID, label, valor, saldo));
		nextID += 1;
	}


	bool debitar(string label, float value){
		if (value > 0 && value <= saldo){
				saldo -= value;
				pushOperation(label, value, saldo);
				return true;
		}
		return false;

	}

	bool creditar(string label, float value){
		if (value > 0){
			saldo += value;
			pushOperation(label, value, saldo);
			return true;
		}
		return false;
	}

	bool tarifa(int i){
		if(extrato[i].descricao == "tarifa"){
			saldo += extrato[i].valor;
			extrato.erase(extrato.begin()+i);
			return true;
		}
		return false;
	
	}	
	
	string getExtratoN(int n){
		stringstream ss;
		if(n < 0)
				return "nem prestou....";

		int i = (int)extrato.size() - n;
		for(; i < extrato.size(); i++){
			ss << extrato[i].toString() << endl;
		}
		return ss.str();
	}
	
	/*string Extrato(){
		stringstream ss;
		for(int i = 0; i < extrato.size(); i++){
			ss << extrato[i].toString() << endl;
		}
		return ss.str();
	} //retorna as última n operacoes
	*/

};


struct Controller{
	Conta conta;
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "help")
            out << "show; init <numero>; deposito <valor>; saque <valor>; tarifa <valor>; extrono <id>; extrato <int> ; end";
        else if(op == "init"){            
			int numero;
            in >> numero;
			conta =Conta(numero);
            out << "success";
        }else if(op == "show"){
			out << conta.toString();
        }else if(op == "deposito"){
			float valor;
            in >> valor;
			conta.creditar(op, valor);
        }else if(op == "saque"){
			float valor;
            in >> valor;
			conta.debitar(op, valor);
        }/*else if(op == "tarifa"){
            string id;
        }else if(op == "extorno"){
            string id;
        }else if(op == "extrato"){
            string id;*/
        return out.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            cout << line << endl;
            cout << "  " << shell(line) << endl;
        }
    }
};

int main(){
	Controller cont;
	cont.exec();
    return 0;
}

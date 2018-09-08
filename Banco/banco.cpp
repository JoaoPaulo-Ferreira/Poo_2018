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
        ss << setw(2) << indice << ": " << setw(10) << descricao << ": " << setw(6) << valor << ": " << setw(6) << saldo;
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
        if (value > 0 /*&& value <= saldo*/){
            if(label == "tarifa"){
                saldo -= value;
                pushOperation(label, -value, saldo);
                return true;
            }else if(value <= saldo){
                saldo -= value;
                pushOperation(label, -value, saldo);
            return true;
            }
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

    bool extorno(int i){
        if(extrato[i].descricao == "tarifa"){
            saldo += -(extrato[i].valor);
            pushOperation("extorno", -(extrato[i].valor), saldo);
            return true;
        }
        return false;
    }

    string extratoN(int n){
        stringstream ss;
        if(n < 0 || n > extrato.size())
                return "failure: indice invalido";
        ss << endl;
        for(int i  = (extrato.size() - n); i < extrato.size(); i++){
            ss << extrato[i].toString() << endl;
        }
        return ss.str();
    }

    string show_extrato(){
        stringstream ss;
        ss << endl;
        for(int i = 0; i < (int )extrato.size(); i++){
            ss << extrato[i].toString() << endl;
        }
        return ss.str();
    }


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
            conta.creditar(op, valor) ? out << "success" : out << "failure: valor inválido";
        }else if(op == "saque"){
            float valor;
            in >> valor;
            conta.debitar(op, valor) ? out << "success" : out << "failure: saldo insuficiente";
        }else if(op == "tarifa"){
            float valor;
            in >> valor;
            conta.debitar(op, valor)? out << "success" : out  << "failure: saldo insuficiente";
        }else if(op == "extorno"){
            int valor;
            in >> valor;
            conta.extorno(valor) ? out << "success: indice " << valor << " extornado" << endl : out << "failure: indice " << valor <<" invalido";
            while(in >> valor)
            conta.extorno(valor) ? out << "\n  success: indice " << valor << " extornado" : out << "\n  failure: indice " << valor <<" invalido";
        }else if(op == "extratoN"){
            int valor;
            in >> valor;
            out << conta.extratoN(valor);
        }else if(op == "extrato")
            out << conta.show_extrato();
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



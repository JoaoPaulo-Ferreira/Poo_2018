#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Cliente{
    string id;
    string fone;
    Cliente(string id = "fulano", string fone = "0000"){
        this->id = id;
        this->fone = fone;
    }
    string toString(){
        stringstream ss;
        ss << this->id << ":" << this->fone;
        return ss.str();
    }
};

struct Sala{
    vector< Cliente * > cadeiras;

    Sala(int qtd = 0){
        for(int i = 0; i < qtd; i++)
            cadeiras.push_back(nullptr);
    }

    bool existe(int id){
        if(cadeiras[id] != nullptr)
            return true;
        return false;
    }

    bool reservar(Cliente *cliente, int ind){

        int qtd = cadeiras.size();
        if((ind < 0) || (ind >= qtd)){
            cout << "fail: essa cadeira nao existe" << endl;
            return false;
        }

        if(existe(ind)){
            cout << "fail: essa cadeira ja esta ocupada" << endl;
            return false;
        }

        for(int i = 0; i < (int)cadeiras.size(); i++){
            if(existe(i) && (cadeiras[i]->id) == (cliente->id)){
                cout << "fail: voce ja esta no cinema" << endl;
                return false;
            }
        }
//        cout << cadeiras[0]->id << " == " << cliente.id << endl;
        cadeiras[ind] = cliente;
//        cout << "out reservar" <<endl;
        return true;
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for ( int i = 0; i < (int)cadeiras.size(); i++){
            ss << cadeiras[i]->toString() << " ";
//            cout << cadeiras[i]->id << endl;

        }
        ss << "]";
        cout  << "help" << endl;
        return ss.str();
    }
};

int main(){
    Sala sala;
    string op;
    while(true){
        cin >> op;
        if(op == "show"){
            cout << sala.toString() << endl;
        }else if(op == "init"){
            int qtd;
            cin >> qtd;
            sala = Sala(qtd);
            cout << "sala criada com " << qtd << " cadeiras" << endl;
        }else if(op == "r"){
            string nome, fone;
            int ind;
            cin >> nome >> fone >> ind;
            Cliente c (nome,fone);
            if(sala.reservar(&c,ind))
                cout << "done" << endl;
        }
    }
}

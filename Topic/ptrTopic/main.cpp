#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>

#define INVALID -1
using namespace std;

struct Cliente{
    string id;
    int idade;
    Cliente(string id = "lero", int idade = 0){
        this->id = id;
        this->idade = idade;
    }

    string toString(){
        stringstream f;
        f << id << ":" << idade;
        return f.str();
    }
};


struct Topic{
    int pref;
    vector<Cliente *> cadeiras;

    Topic(int lot = 0, int pref = 0) : cadeiras(lot, nullptr), pref(pref){
    }


    string toString(){
        stringstream s;
        s << "[ ";
        for(int i = 0; i < (int)cadeiras.size(); i++){
            if(cadeiras[i] == nullptr)
                i < pref ? s << " @ " : s << " = ";
            else
                s << " " << cadeiras[i]->toString();
        }
        s << "]";
        return s.str();
    }

    int getNormalIndex(){
        for(int i = pref; i < (int)cadeiras.size(); i++){
//            cout << "normal index " << "pref = " << pref << "lot = " << lot << "i = " << i << endl;
            if(cadeiras[i] == nullptr)
                return i;
        }
        return INVALID;
    }

    int getPriorIndex(){
        for(int i = 0; i < pref; i++){
            if(cadeiras[i] == nullptr)
                return i;
        }
        return INVALID;
    }

    bool alreadyIS(string nome){
        for(int i = 0; i < (int)cadeiras.size(); i++){
            if(cadeiras[i] != nullptr && cadeiras[i]->id == nome)
                return true;
        }
        return false;
    }

    bool insert(string id, int idade){
        int index;
        if(idade < 60){
            index = getNormalIndex();
            if(index != INVALID){
                cadeiras[index] = new Cliente(id, idade);
//                cout << "que falha o que ? " << endl;
                return true;
            }
            index = getPriorIndex();
            if(index != INVALID){
                cadeiras[index] = new Cliente(id, idade);
                return true;
            }
        }

        if(idade >= 60){
            index = getPriorIndex();
            if(index != INVALID){
                cadeiras[index] = new Cliente(id, idade);
                return true;
            }
            index = getNormalIndex();
            if(index != INVALID){
                cadeiras[index] = new Cliente(id, idade);
                return true;
            }
        }
        return false;
    }

    bool remove(string nome){
        for(int i = 0; i < (int)cadeiras.size(); i++){
            if(cadeiras[i] != nullptr && cadeiras[i]->id == nome){
                delete(cadeiras[i]);
                cadeiras[i] = nullptr;
                return true;
            }
        }
        return false;
    }
};



struct Controller{
    Topic topic;


    string shell(string request){
        stringstream in(request);
        stringstream out;
        string op;
        in >> op;

        if( op == "help"){
            out << "init <lot><pref>; show; in <nome><idade>; out<nome>; end";
        }
        if( op == "init"){
            int lot, pri;
            in >> lot >> pri;
            topic = Topic(lot, pri);
            out << "done";
        }

        if( op == "in"){
            string nome;
            int idade;
            in >> nome >> idade;
            if(!topic.alreadyIS(nome))
                topic.insert(nome, idade)? out << "done" : out << "fail: Topic lotada";
            else
                out << "fail: " << nome << " ja esta na topic";
        }

        if(op == "show")
            out << topic.toString();

        if(op == "out"){
            string nome;
            in >> nome;
            topic.remove(nome)? out << "done" : out << "fail: " << nome << " nao está na topic";
        }


        return out.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << line;
            if(line == "end")
                    return;
            cout << "    " << shell(line)<< endl;

        }
    }

};

int main(){
    cout << "stating ..." << endl;
    Controller c;
    c.exec();
    return 0;
}

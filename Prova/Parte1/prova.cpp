#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Fone {
public:
    string id;
    string number;

    Fone(string id = "", string number = ""){
        this->id = id;
        this->number = number;
    }

    static bool validate(string number){
        string data = "1234567890()- ";
        for(auto c : number)
            if(data.find(c) == string::npos)
                return false;
        return true;
    }
};

class Contato {
    string name;
    vector<Fone> fones;
    bool favorited = false;
public:
    Contato(string name = ""){
        this->name = name;
    }
    ~Contato(){}

    string getName(){
        return name;
    }

    void setFav(){
        favorited = true;
    }

    void unsetFav(){
        favorited = false;
    }

    void addFone(Fone fone){
        if(!Fone::validate(fone.number))
            throw string("fone " + fone.number + " invalido");
        fones.push_back(fone);
    }

    void rmFone(size_t indice){
        if(indice < 0 || indice >= fones.size())
            throw string("indice " + to_string(indice) + " nao existe");
        fones.erase(fones.begin() + indice);
    }

    vector<Fone> getFones(){
        vector<Fone> resp;
        for(auto fone: fones)
            resp.push_back(fone);
        return resp;
    }

    string toString(){
        string saida;
        if (favorited == false){
            saida = "- " + this->name + " C ";
        }else{
            saida = "@ " + this->name + " C ";
        }
        int i = 0;
        for(auto fone : getFones())
            saida += "[" + to_string(i++) + ":" + fone.id + ":" + fone.number + "]";
        return saida;
    }
};

class Agenda {
    map<string, Contato> contatos;
    map<string, Contato*> favoritos;

public:
    void addContato(Contato cont){
        string name = cont.getName();
        if(contatos.count(name) == 1)
            throw string("contato " + name + " ja existe");
        contatos[name] = cont;
    }

    void rmContato(string name) {
        favoritos.erase(name);
        contatos.erase(name);
    }

    Contato * getContato(string name){
        auto it = contatos.find(name);
        if(it == contatos.end())
            throw string("  contato " + name + " nao existe");        
        Contato *cont = &it->second;
        
        if(contatos.count(name))
            return &contatos[name];
       
    }
            //PROVA
    void favoritar(string name){
        auto it = contatos.find(name);
        if (it == contatos.end())
            throw string("contato " + name + " nao existe");
        contatos[name].setFav();
        favoritos[name] = &it->second;
    }

    void desfavoritar(string name){
        auto it = contatos.find(name);
        if (it == contatos.end())
            throw string("contato " + name + " nao existe");
        contatos[name].unsetFav();
        auto itfav = favoritos.find(name);
        itfav->second = nullptr;
        favoritos.erase(itfav);
    }

    string toStringFav(){
        stringstream saida;
        for(auto it = favoritos.begin(); it != favoritos.end(); it++){
            saida << it->second->toString();
            saida << "\n";
        }
        return saida.str();
    }
            //FIM

    vector<Contato> getContatos(){
        vector<Contato> resp;
        for(auto& par : contatos)
            resp.push_back(par.second);
        return resp;
    }

    vector<Contato> search(string pattern){
        vector<Contato> resp;
        for(auto& par : contatos)
            if(par.second.toString().find(pattern) != string::npos)
                resp.push_back(par.second);
        return resp;
    }

    string toString(){
        string saida = "";
        for(auto contato : getContatos())
            saida += contato.toString() + "\n";
        return saida;
    }
};

class Controller {

    Agenda agenda;
public:

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "addContato"){
            string name, id_number;
            ss >> name;
            Contato cont(name);
            while(ss >> id_number){
                string id, fone;
                stringstream ssfone(id_number);
                getline(ssfone, id, ':');
                ssfone >> fone;
                cont.addFone(Fone(id, fone));
            }
            agenda.addContato(cont);
        }
        else if(op == "rmFone"){
            string name;
            int indice;
            ss >> name >> indice;
            agenda.getContato(name)->rmFone(indice);
        }
        else if(op == "rmContato"){
            string name;
            ss >> name;
            agenda.rmContato(name);
        }
        else if(op == "agenda"){
            cout << agenda.toString();
        }
        else if(op == "search"){
            string pattern;
            ss >> pattern;
            auto resp = agenda.search(pattern);
            for(auto contato : resp)
                cout << contato.toString() << endl;
        }else if(op == "fav"){
            string name;
            ss >> name;
            agenda.favoritar(name);
            cout << "done\n";
        }else if(op == "unfav"){
            string name;
            ss >> name;
            agenda.desfavoritar(name);
            cout << "done\n";
        }else if(op == "favorited"){
            cout << agenda.toStringFav();
        }
        else
            cout << "comando invalido" << endl;
    }


    void exec() {
        string line = "";
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            try {
                shell(line);
            } catch(const string& e) {
                cout << e << endl;
            }
        }
    }
};

int main()
{
    Controller controller;
    controller.exec();
    return 0;
}
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
class Nota{
public:
    string titulo;
    string texto;
    Nota(string _titulo = "", string _texto = "") : titulo(_titulo), texto(_texto){}

    string toString(){
        return this-> titulo + " : " + this->texto;
    }

};

class User{
    // string nome;
    string pass;
    public:
    vector<Nota> notas;
    
    User(string _pass = ""): /*nome(_nome),*/ pass(_pass){}

    void verifyPass(string _pass){
        // return _pass == pass ? true : false;
        if(_pass == pass)
            return;
        throw "fail: password errado";
    }

    void changePass(string old, string newPass){
        verifyPass(old);
        pass = newPass;
    }

    void addNote(string titulo, string texto){
        for(size_t i = 0; i < notas.size(); i++)
            if(notas[i].titulo == titulo)
                throw "titulo ja existe";
        notas.push_back(Nota(titulo, texto ));
    }

    void rmNote(string titulo){
        size_t i;
        for(i = 0; i < notas.size(); i++)
            if(notas[i].titulo == titulo)
                break;
        if(i == notas.size())
            throw "fail: nota nao encontrada";
        notas.erase(notas.begin() + i);
    }

    string showNotes(){
        stringstream out;
        size_t i;
        out << endl;
        for(i = 0; i < notas.size(); i++){
            out << notas[i].toString() << endl;
        }
        return out.str();
    }
};

class Sistema{
    map<string, User> usuarios;
    string adminName;
    public:
    Sistema(){
        adminName = "admin";
        addUser("admin", "admin");

    }
    bool exist(string name){
        return usuarios.find(name) != usuarios.end() ? true : false;
    }


    void addUser(string id, string senha){
        auto it = usuarios.find(id);
        if(it != usuarios.end())
            throw "fail: usuario ja existe";
        usuarios.insert(pair<string, User>(id,User(senha)));
    }

    User* getUser(string name){
        auto it = usuarios.find(name);
        return it != usuarios.end() ? &it->second : throw "fail: usarname nao existe";
    }

    string showUsers(){
        stringstream out;
        out << endl;
        for(auto it = usuarios.begin(); it != usuarios.end(); it++){
            out << it->first << endl;
        }
        return out.str();
    }

};


class gerLogin{
    User * current;
    Sistema * sistema;
public:
    gerLogin(Sistema *sistema){
        this->sistema = sistema;
        current = nullptr;
    }

    User& getUser(){
        if(current == nullptr)
            throw "fail: ninguem logado";
        return *current;
    }

    void login(string username, string senha){
        if(current != nullptr)
            throw "fail: ja existe alguem logado";
        User* user = sistema->getUser(username);
        user->verifyPass(senha);
        current = user;
    }

    void logout(){
        if(current == nullptr)
            throw "fail: ninguem logado";
        current = nullptr;
    }
};
class Controller{
    Sistema sistema;
    gerLogin gl;
    // User * current;

public:
    Controller(): gl(&sistema){
        // current = nullptr;
    }
    string shell(string comand){
        stringstream in(comand), out;
        string op;
        in >> op;
        if(op == "addUser"){
            string id, senha;
            in >> id >> senha;
            sistema.addUser(id, senha);
            out << "usuario criado";
        }else if(op == "showUsers"){
            out << sistema.showUsers();
        }else if(op == "login"){
            string username, senha;
            in >> username >> senha;
            gl.login(username, senha);
            out << "done";
        }else if(op == "logout"){
            gl.logout();
            out << "done";
        }else if(op == "changePass"){
            string oldPass, newPass;
            in >> oldPass >> newPass;
            gl.getUser().changePass(oldPass, newPass);
            out << "done";
        }else if(op == "addNote"){
            string titulo, texto;
            in >> titulo;
            getline(in, texto);
            gl.getUser().addNote(titulo, texto);
            out << "done";
        }else if(op == "rmNote"){
            string titulo;
            in >> titulo;
            gl.getUser().rmNote(titulo);
            out << "done";
        }else if(op == "showNotes"){
            out << gl.getUser().showNotes();
        }
        return out.str();
    }

    void exec(){
        string input;
        while(1){
            getline(cin, input);
            cout << input << endl;
            if(input == "end")
                break;
            try{
                cout << "  " << shell(input) << endl;
            }catch(const char * excep){
                cout << excep << endl;
            }
        }
    }

};

int main(){
    Controller cont;
    cont.exec();
    return 0;
}
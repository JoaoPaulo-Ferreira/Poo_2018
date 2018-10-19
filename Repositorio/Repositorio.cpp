#include <iostream>
#include <sstream>
#include <map>
#include <cstdlib>
using namespace std;

class Aluno{
    string nome;
    string curso;

public:
    Aluno(string curso="", string nome="jp"){
        this->curso = curso;
        this->nome = nome;
    }
    
    string toString(){
        return  " " + curso + " " + nome;
    }
};


class Professor{
    string nome;
    string nivel;

public:
    Professor( string _nome = "davi", string _nivel = "doutor"){
        nome = _nome;
        nivel = _nivel;
    }

    string toString(){
        return  " " + nome + " " + nivel;
    }
};

class Disciplina{
    string curso;
    string nome;

public:
    Disciplina(){}

    Disciplina(string _curso, string _nome){
        curso = _curso;
        nome = _nome;
    }

    string toString(){
        return " " + curso + " " + nome;
    }
};

template <typename K, typename V>
class Rep{
    map<K, V>data;
    public:

    bool exist(K key){
        return (data.find(key) != data.end()) ? true : false;
    }

    auto find(K key){
        return data.find(key);
    }

    void add(K key, V value){
        if(exist(key))
            throw "ID já existe";
        data[key] = value;    
    }

    string toString(K key){
        stringstream s;
        auto it = find(key);
        if(it == data.end())
            throw "Isto não existe";
        s << key << it->second.toString() << "\n";
        return s.str(); 
    }

    string show_ALL(){
        stringstream s;
        s << "\n";
        for(auto it = data.begin(); it != data.end(); it++){
            s << it->first + it->second.toString() + "\n";
        }
        return s.str();
    }

    void del(K key){
        if(!exist(key))
            throw "Isto não existe";
        for(auto it = data.begin(); it != data.end(); it++){
            if(it->first == key){
                data.erase(it);
            }
        }
    }

    

};

class Controller{
    Rep<string, Aluno> Alunos;
    Rep<string, Professor> Professores;
    Rep<string, Disciplina> Disciplinas;

public:
    string shell(string comando){
        stringstream in(comando), out;
        string op;
        in >> op;
        if(op == "addAlu"){
            string v1, v2, v3;
            in >> v1 >> v2;
            getline(in,v3);
            Alunos.add(v1, Aluno(v2,v3));
            out << "done";
        }else if(op == "addPro"){
            string v1, v2, v3;
            in >> v1 >> v2;
            getline(in,v3);
            Professores.add(v1, Professor(v2,v3));
            out << "done";
        }else if(op == "addDis"){
            string v1, v2, v3;
            in >> v1 >> v2;
            getline(in,v3);
            Disciplinas.add(v1, Disciplina(v2,v3));
            out << "done";
        }else if(op == "getAlu"){
            string v1;
            in >> v1;
            out << Alunos.toString(v1);
        }else if(op == "getPro"){
            string v1;
            in >> v1;
            out << Professores.toString(v1);
        }else if(op == "getDis"){
            string v1;
            in >> v1;
            out << Disciplinas.toString(v1);
        }else if(op == "showAlu"){
            out << Alunos.show_ALL();
        }else if(op == "showPro"){
            out << Professores.show_ALL();
        }else if(op == "showDis"){
            out << Disciplinas.show_ALL();
        }else if(op == "rmAlu"){
            string v1;
            in >> v1;
            Alunos.del(v1);
            out << "Done";
        }else if(op == "rmPro"){
            string v1;
            in >> v1;
            Professores.del(v1);
            out << "Done";
        }else if(op == "rmDis"){
            string v1;
            in >> v1;
            Disciplinas.del(v1);
            out << "Done";
        }
        return out.str();
    }

    void exec(){
        string comando;
        while(1){
            getline(cin, comando);
            if(comando == "end")
                break;
            try{
                cout << "$" << comando << endl;
                cout << "\t" << shell(comando) << endl;
            }catch(const char * e){
                cout << e << endl;
            }
        }
    }
};

int main(){
    Controller c;
    c.exec();
    // Rep<int, Aluno> Alunos;
    // Rep<int, Professor> Professores;
    // Rep<string, Disciplina> Disciplinas;
    // Alunos.add(100, Aluno("Joao_Paulo", " abestadooooo"));
    // Professores.add(10, Professor("David", " prêfessor"));
    // Disciplinas.add("QXD123", Disciplina("!@!@", "abestadooooo"));
    // try{
    //     cout << Alunos.toString(100);
    //     cout << Professores.toString(10);
    //     // cout << Disciplinas.toString(10);
    //     cout << Alunos.show_ALL();
    //     Alunos.del(100);
    //     // cout << Alunos.toString(100);
    //     cout << Alunos.show_ALL();
    //     cout << Disciplinas.toString("QXD123");

    // }catch(const char * e){
    //     cout << e << endl;
    // }
    return 0;
}
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

enum prof_Classe{
    A = 3000,
    B = 5000,
    C = 7000,
    D = 9000,
    E = 11000
};
    
class Funcionario{
public:
    float bonus;
    string nome;
    int max_diarias;
    int diarias;
    Funcionario(string nome):nome(nome){}
    virtual float calcularSalario() = 0;
    virtual string toString() = 0;
    virtual void setBonus(float p_bonus){
        if(p_bonus < 0)
            throw "fail: bonus invalido";
        bonus = p_bonus;
    }
    virtual void addDiaria(){
        if(diarias == max_diarias)
            throw "fail: maximo de diarias atingido";
        this->diarias++;
    }
    virtual ~Funcionario(){};
};

class Professor : public Funcionario{
public:
    char classe;
    Professor(string nome, char classe) :Funcionario(nome), classe(classe){
        max_diarias = 2;
        diarias = 0;
        setClasse(classe);
    }

    ~Professor(){}

    void setClasse(char classe){
        if(classe < 'A' || classe > 'E')
            throw "fail: classe inválida";
        this->classe = classe;
    }

    virtual float calcularSalario(){
        float sal;
        switch(classe){
            case 'A':
                sal = A + 100 * diarias; 
            break;
            case 'B':
                sal = B + 100 * diarias;
            break;
            case 'C':
                sal = C + 100 * diarias;
            break;
            case 'D':
                sal = D + 100 * diarias;
            break;
            case 'E':
                sal = E + 100 * diarias;
            break;
            default:
                sal = 0;
                break;
        }
        return sal + bonus;
    }
    
    virtual string toString(){
        return "Prof " + nome + " classe " + 
                classe  + "\n\tsalário " + to_string(calcularSalario());
    }


};

class Terceirizado : public Funcionario{
    public:
    int horas;
    bool insalubre;
    Terceirizado(string nome, bool insalubre, int horas) : Funcionario(nome), insalubre(insalubre){
        max_diarias = 0;
        diarias = 0;
        this->horas = horas;
    }

    ~Terceirizado(){}

    virtual void addDiaria(){
        throw "Terceirizado nao recebe diaria";
    }

    virtual float calcularSalario(){
        float sal;
        sal = 4 * horas;
        if(insalubre)
            sal += 500;
        return sal;
    }
    
    virtual string toString(){
        return "Terceirizado " + nome +
                 "\n\tsalário " + to_string(calcularSalario());
    }

};

class Tecnico : public Funcionario{
public:
    int nivel;
    Tecnico(string nome, int nivel) : Funcionario(nome), nivel(nivel){}

    ~Tecnico(){}

    virtual float calcularSalario(){
        float sal;
        sal = 3000 + 300 * nivel;
        return sal;
    }

    virtual string toString(){
        return "Tecnico " + nome + " nível " + to_string(nivel) +
                 "\n\tsalário " + to_string(calcularSalario());
    }
};

template <typename T>
class Rep{
public:
    map<string,T> data;

    void add(string name, T t){
        auto it = data.find(name);
        if(it != data.end())
            throw "fail: Funcionario ja existe";
        data[name] = t;
    }

    void rm(string name){
        auto it = data.find(name);
        if(it == data.end())
            throw "fail: Funcionario não existe";
        delete it->second;
        data.erase(it);
    }

    string show(string nome){
        stringstream out;
        auto it = data.find(nome);
        if(it == data.end())
            throw "fail: Funcionario nao existe";
        out << it->second->toString() << endl;
        return out.str();
    }

    string show_All(){
        stringstream out;
        out << endl;
        for(auto it = data.begin(); it != data.end(); it++){
            out << it->second->toString() << endl;
        }
        return out.str();
    }

    void add_Diaria(string nome){
        auto it = data.find(nome);
        if(it == data.end())
            throw "fail: Funcionario nao existe";
        it->second->addDiaria();
    }

    void set_Bonus(float total_bonus){
        float parcial_bonus = total_bonus / (int)data.size();
        
        for(auto it = data.begin(); it != data.end(); it++){
            it->second->setBonus(parcial_bonus);
        }
    }

};

class Controller{
public:
    Rep<Funcionario *>sistema;

    string shell(string comand){
        stringstream in(comand), out;
        string op;
        in >> op;
        if(op == "addProf"){
            string nome, classe;
            in >> nome;
            in >> classe;
            sistema.add(nome, new Professor(nome,classe.c_str()[0]));
            out << "Done";
        }else if(op == "addTerc"){
            string nome, insalubre;
            int horas;
            in >> nome;
            in >> insalubre;
            in >> horas;
            sistema.add(nome, new Terceirizado(nome, (insalubre == "T" ? true : false ), horas));
            out << "Done";   
        }else if(op ==  "addAdm"){
            string nome;
            int nivel;
            in >> nome;
            in >> nivel;
            sistema.add(nome, new Tecnico(nome, nivel));
            out << "Done";
        }else if(op == "show"){
            string name;
            in >> name;
            return sistema.show(name);
        }else if(op == "rm"){
            string name;
            in >> name;
            sistema.rm(name);
            out << "Done";
        }else if(op == "showAll"){
            return sistema.show_All();
        }else if(op == "addDiaria"){
            string nome;
            in >> nome;
            sistema.add_Diaria(nome);
            out << "Done";
        }else if(op == "setBonus"){
            float bonus;
            in >> bonus;
            sistema.set_Bonus(bonus);
            out << "Done";
        }
        return out.str();
    }

    void exec(){
        string line;
        while(1){
            getline(cin, line);
            cout << line << endl;
            if(line == "end")
                break;
            try{
                cout << "   " << shell(line) << endl;
            }catch(const char * e){
                cout << e << endl;
            }
        }
    }

};

int main(){
    Controller c;
    c.exec();
    return 0;
}
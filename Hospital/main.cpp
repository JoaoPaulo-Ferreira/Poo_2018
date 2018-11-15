#include <iostream>
#include <sstream>
#include <algorithm>
#include "patient.h"
#include "rep.h"
#include "doctor.h"

using namespace std;

class Controller{
    Rep<User *>Usuarios;
public:
    string shell(string line){
        stringstream in(line), out;
        string op;
        in >> op;
        if(op == "addPats"){
            string name, diag;
            while(getline(in, name, '-')){
                in >> diag;
                name.erase(remove( name.begin(), name.end(), ' '), name.end());//erasing all whitespaces read by getline
                Usuarios.add(name, new Patient(name, diag));
            }
            out << "Done";
        }else if (op == "addDocs"){
            string name, spec;
            while(getline(in, name, '-')){
                in >> spec;
                name.erase(remove( name.begin(), name.end(), ' '), name.end());//erasing all whitespaces read by getline
                Usuarios.add(name, new Doctor(name, spec));
            }
            out << "Done";
        }else if (op == "tie"){
            string doc, pat;
            in >> doc;
            while(in >> pat)
                Usuarios.rep_tie(doc, pat);
            out << "Done\n";
        }else if (op == "msg"){
            string from,to ,text;
            in >> from >> to;
            getline(in, text);
            Usuarios.rep_sendMsg(from, to, text);
            out << "Done";
        }else if (op == "inbox"){
            string name;
            in >> name;
            out << Usuarios.rep_read(name);
        }else if (op == "see"){
            string name;
            in >> name;
            out << Usuarios.show(name);
        }else if (op == "seeAll"){
            out << Usuarios.show_All();
        }
        return out.str();
    }

    void exec(){
        string line;
        while(1){
            getline(cin,line);
            cout << "  " << line << endl;
            if(line == "end")
                break;
            try{
                cout << shell(line) << endl;
            }catch(const char * e){
                cout << e << endl;
            }
        }
    }
};


int main(){
    Controller cont;
    cont.exec();
    return 0;
}

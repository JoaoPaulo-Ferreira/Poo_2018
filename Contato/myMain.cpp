#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;



class Fone{
    string label;
    string numero;

    public:

    Fone(string _numero, string _label = ""): label(_label), numero(_numero){
    }

    bool validate(){
	if(numero.length() < 9) 
		return false;
       	return true; 	
    }

    string toString(){
	stringstream ss;
	ss << label << ":" << numero;
	return ss.str();
    }

};

class Contato{
	string nome;
	vector<Fone> fones;
public:
	Contato(string _nome = "vazio") : nome(_nome){		
	}	

	Contato(string _nome, Fone fone ){
		nome = _nome;
		fones.push_back(fone);
	}


};

int main(){
//    string line, palavra;
//    getline(cin, line);
//    stringstream ss(line);
//    ss >> palavra;
//    while(ss >> palavra){
//        cout << palavra.substr(palavra.find(':',0), palavra.length());
//    }


    cout << setprecision(2) << 132.35 << endl;



    return 0;
}

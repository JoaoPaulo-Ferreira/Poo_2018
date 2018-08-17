#include <iostream>
#include <string>
#include <stdlib.h>
#define vazia 1
#define cheia 0
using namespace std;



struct Cliente{
    string id;
    string fone;

    Cliente(string _id = "", string _fone = "00"){
        id = _id;
        fone = _fone;
    }

    void show(){
        cout << "Nome:  " << id <<" | Tel:  "<< fone << endl;
    }
};

struct Cadeira{
    int id;
    Cliente cliente();
    Cadeira(int _id = vazia){
        id = _id;
        // cout << "really?" << endl;

    }
};

struct Sala{
    int nCadeiras;
    int cVazias;
    Cadeira *vet;
    Sala(int _nCadeiras){
        nCadeiras = _nCadeiras;
        vet = (Cadeira *)malloc(nCadeiras * sizeof(Cadeira));
        for (int i = 0; i < nCadeiras; i++){
            vet[i] = Cadeira();
        }
        cVazias = nCadeiras;
        cout << "\tSala criada com "<< nCadeiras<<" cadeiras"<< endl;
    }

    void show(){
        cout << "[  ";
        for (int i = 0; i < nCadeiras; i++){
            if(vet[i].id == vazia)
                cout << "- ";
        }
        cout << "  ]"<< endl;
    }

    int reserva(string _nome, string tel, int cadID){
        if(cadID > nCadeiras || cadID < 0)
            return 0;

        for(int i = 0; i < nCadeiras; i++){
            if(vet[i].id == _nome){
                cout << "fail: "<< _nome << "ja esta no cinema" << endl;
                return 0;
            }

        }

        // if(vet[cadID].id == vazia)
    }
};

int main(){
    // Cliente davi("davi");
    // davi.show();
    Sala sala(5);
    sala.show();

}

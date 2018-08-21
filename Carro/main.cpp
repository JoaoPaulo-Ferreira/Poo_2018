#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define maxPASS 2
#define maxGAS 10

struct Carro{
    int pass;
    float gas;
    float km;

    Carro(int _pass = 0, float _gas = 0, float _km = 0){
        pass = _pass;
        gas = _gas;
        km = _km;
    }

    void show(){
        cout << "\tpass: " << pass << ", gas: " << gas << ", km: " << km << endl;
    }

    void embarque(){
        if(pass < maxPASS){
            pass++;
            cout << "\tdone" << endl;
        }else
            cout << "\tfail: limite de pessoas atingido" << endl;
    }

    void desembarque(){
        if(pass > 0){
            cout << "\tdone" << endl;
            pass--;
        }else
            cout << "\tfail: nao ha ninguem no carro" << endl;
    }

    void abastecer(float newGas){
        if(newGas > 0 ){
            gas += newGas;
            if(gas > maxGAS)
                gas = maxGAS;
            cout << "\tdone" << endl;
            return;
        }
        cout << "\tfail: valor negativo de combustivel" << endl;
    }

    void andar(float distance){
        if(pass > 0 ){
            if(gas > 0){
                if(distance/10 <= gas){
                    gas = gas - distance/10;
                    km += distance;
                    cout << "\tdone" << endl;
                    return;
                }else{
                    cout << "\tfail: gasolina insuficiente" << endl;
                    return;
                }
            }else{
                cout << "\tfail: sem gasolina" << endl;
                return;
            }
        }else{
            cout << "\tfail: nao ha ninguem no carro" << endl;
        }

    }
    /*
    void charge(int carga){
        bateria += carga;
        if(bateria > limiteBateria)
            bateria = limiteBateria;
    }
    float soma(float a, float b, bool * deu_certo){
        *deu_certo = false;
        if(!gastarBateria())
            return 0;
        *deu_certo = true;
        return a + b;
    }
    float div(float a, float b, bool * deu_certo){
        *deu_certo = false;
        if(!gastarBateria())
            return 0;
        if(b == 0.0){
            puts("  fail: nao posso dividir por 0");
            return 0;
        }
        *deu_certo = true;
        return a/b;
    }
    bool gastarBateria(){
        if(bateria > 0){
            this->bateria -= 1;
            return true;
        }
        puts("  fail: bateria insuficiente");
        return false;
    }*/
};

int main(){
    string op;
    Carro carro;
    carro.show();
    while(true){
        cin >> op;
        if(op == "help"){
            puts("in/out ; fuel <float>; show; drive <float>; exit");
        }else if(op == "show"){
            carro.show();
        }
        else if(op == "in"){
            carro.embarque();
        }else if(op == "out"){
            carro.desembarque();
        }else if(op == "fuel"){
            float fuel;
            cin >> fuel;
            carro.abastecer(fuel);
        }else if(op == "drive"){
            float distance;
            cin >> distance;
            carro.andar(distance);
        }else if(op == "exit")
            break;
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

enum{
    ISNT_SLEEPY=-2,
    IS_DEAD=-1,
    IS_ALIVE=0,
    DIED_ENEGEY=1,
    DIED_HUNGRY=2,
    DIED_CLEAN=4,
    DIED_ENERGY_HUNGRY=3,
    DIED_ENERGY_CLEAN=5,
    DIED_HUNGRY_CLEAN=6,
    DIED_HUNGRY_CLEAN_ENERGY=7
};

class Pet{
private:
    int energy;
    int hungry;
    int clean;
    int energyMax;
    int hungryMax;
    int cleanMax;
    int diamonds;
    int age;
public:
    Pet(){}
    Pet(int e, int h, int c){
        energyMax = energy = e;
        hungryMax = hungry =  h;
        cleanMax = clean = c;
        diamonds = 0;
        age = 0;
    }

    int getEnergyMax(){
        return energyMax;
    }
    int getHungryMax(){
        return hungryMax;
    }
    int getCleanMax(){
        return cleanMax;
    }
    int getEnergy(){
        return energy;
    }
    int getHungry(){
        return hungry;
    }
    int getClean(){
        return clean;
    }
    int getDiamonds(){
        return diamonds;
    }
    int getAge(){
        return age;
    }
    void incDiamonds(int i = 1){
        diamonds+=i;
    }
    void incAge(int i = 1){
        age+=i;
    }
    void incEnergy(int e = 1){
        (e + energy) < energyMax ? energy += e : energy = energyMax ;
        if(energy < 0) energy = 0 ;
    }
    void setEnergy(int e){
        (e < energyMax) ? energy = e : energy = energyMax;
        if(energy < 0) energy = 0 ;
    }
    void setClean(int c){
        (c < cleanMax) ? clean = c : clean = cleanMax;
        if(clean < 0) clean = 0 ;
    }
    void incHungry(int h = 1){
        (h + hungry) < hungryMax ? hungry += h : hungry = hungryMax ;
        if(hungry < 0) hungry = 0 ;
    }
    void incClean(int c = 1){
        (c + clean) < cleanMax ? clean += c : clean = cleanMax ;
        if(clean < 0) clean = 0 ;
    }

    int checkDeath(){
        int aux = 0;
        if(energy <= 0)
            aux = DIED_ENEGEY;
        if(hungry <= 0)
            aux += DIED_HUNGRY;
        if(clean <= 0)
           aux += DIED_CLEAN;
        return aux;
    }


    string toString(){
        stringstream ss;
        ss << "E:" << getEnergy() << "/" << getEnergyMax() << ", "
           << "H:" << getHungry() << "/" << getHungryMax() << ", "
           << "C:" << getClean() << "/" << getCleanMax() << ", "
           << "D:" << getDiamonds() << ", "
           << "A:" << getAge();
        return ss.str();
    }

//eat - Comer || E - 1, C - 2|| -> || H + 4, A + 1|| pet pode comer o quanto quiser, mas a fome nunca vai ultrapassar o limite maximo
    int toEat(){
        if(!checkDeath()){
            incEnergy(-1);
            incClean(-2);
            incHungry(4);
            incAge();
            return checkDeath();
        }
        return IS_DEAD;
    }

    //# play - || E -  2, H - 1, C - 3 || -> ||A + 1, D + 1||
    int toPlay(){
        if(!checkDeath()){
            incDiamonds();
            incAge();
            incEnergy(-2);
            incHungry(-1);
            incClean(-3);
            return checkDeath();
        }
        return IS_DEAD;
    }

//# sleep - || H - 1 || -> || A = (energyMax - E), E = energyMax ||
    int toSleep(){
        if(!checkDeath()){
            if((energyMax - energy) < 5)
                return ISNT_SLEEPY;
            else{
                incHungry(-1);
                incAge(energyMax - energy);
                setEnergy(energyMax);
                return checkDeath();
            }
        }
        return IS_DEAD;
    }

//# clean - || H - 1, E - 3 || -> || A + 2, C = cleanMax ||
    int toShower(){
        if(!checkDeath()){
            incHungry(-1);
            incEnergy(-3);
            incAge(2);
            setClean(cleanMax);
            return checkDeath();
        }
        return IS_DEAD;
    }

    string translator(int status){
        stringstream flow;
        switch (status) {
            case ISNT_SLEEPY:
                flow << "fail: não está com sono" ;
            break;
            case IS_DEAD:
                flow << "fail: pet morreu";
            break;
            case IS_ALIVE:
//            flow << "fail: pet esta morto";
            break;
            case DIED_ENEGEY:
                flow << "fail: pet morreu sem energia";
            break;
            case DIED_HUNGRY:
                flow << "fail: pet morreu de fome";
            break;
            case DIED_ENERGY_HUNGRY:
                flow << "fail: pet morreu sem energia e de fome";
            break;
            case DIED_CLEAN:
                flow << "fail: pet morreu de sujeira";
            break;
            case DIED_ENERGY_CLEAN:
                flow << "fail: pet morreu sem energia e de sujeira";
            break;
            case DIED_HUNGRY_CLEAN:
                flow << "fail: pet morreu de fome e de sujeira";
            break;
            case DIED_HUNGRY_CLEAN_ENERGY:
                flow << "fail: pet morreu de tudo";
            break;
        }
        return flow.str();
    }
};

struct Controller{
    Pet pet;
    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "help")
            out << "init <i><i><i>; show; play; eat; sleep; clean; end";
        else if(op == "init"){
            int numero[3];
            in >> numero[0] >> numero[1] >> numero[2];
            pet = Pet(numero[0],numero[1],numero[2]);
            out << "success";
        }else if(op == "show"){
            out << pet.toString();
        }else if(op == "play"){
            out << pet.translator(pet.toPlay());
        }else if(op == "eat"){
            out << pet.translator(pet.toEat());
        }else if(op == "sleep"){
            out << pet.translator(pet.toSleep());
        }else if(op == "clean"){
            out << pet.translator(pet.toShower());
        }
        return out.str();
    }


    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                break;
            cout << line << endl;
            cout << "  " << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}


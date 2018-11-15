#include "patient.h"
#include "doctor.h"
#include <sstream>
#include <iostream>

Patient::Patient(std::string name = "", std::string diag = ""):User(name), diag(diag){}
Patient::~Patient(){}

std::string Patient::readMsg(){
    std::stringstream out;
    for(size_t i = 0; i < inbox.size(); i++){
        out << inbox[i].toString();
    }
    return out.str();
}

std::string Patient::getDocs(size_t i = 0){
    if(i == d_list.size())
        return "";
    return d_list[i]->name + " " + getDocs(i+1);
}

std::string Patient::toString(){
    return "Pat: " + this->name + ":" + this->diag + "\tDocs: [" + getDocs() + "]" ;
}

void Patient::sendMsg(std::string to, std::string text){
    for(size_t i = 0; i < d_list.size(); i++){
        if(d_list[i]->name == to)
            d_list[i]->inbox.push_back(Msg(to, text));
    }
}

void Patient::sendMsg(std::string from, std::string to, std::string text){
    for(size_t i = 0; i < d_list.size(); i++){
        if(d_list[i]->name == to){
            d_list[i]->inbox.push_back(Msg(from, text));
            return;
        }
    }
    throw "fail: Eles nao se conhecem";
}

void Patient::tie(void * d){
    Doctor * doc = (Doctor *)d;
    this->d_list.push_back(doc);
}
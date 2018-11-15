#ifndef _REP_H_
#define _REP_H_
#include <map>
#include <iostream>
#include <sstream>

template<typename T>
class Rep{
public:
    std::map<std::string, T> data;


    void add(std::string name, T t){
        auto it = data.find(name);
        if(it != data.end())
            throw "fail: ja existe";
        data[name] = t;
        // std::cout << "in add" << data[name]->toString();
    }

    void rm(std::string name){
        auto it = data.find(name);
        if(it == data.end())
            throw "fail: não existe";
        delete it->second;
        data.erase(it);
    }

    void rep_tie(std::string doc, std::string pat){
        auto it_doc = data.find(doc);
        auto it_pat = data.find(pat);
        if(it_pat == data.end() || it_doc == data.end())
            throw "fail: Usuario(s) inválido(s)";
        data[doc]->tie(it_pat->second);
    }

    std::string show(std::string name){
        std::stringstream out;
        auto it = data.find(name);
        if(it == data.end())
            throw "fail: Usuario nao existe";
        out << it->second->toString() << std::endl;
        return out.str();
    }

    std::string rep_read(std::string name){
        auto it = data.find(name);
        if(it == data.end())
            throw "Fail: Usuario nao existe";
        return it->second->readMsg();
    }

    void rep_sendMsg(std::string from, std::string to, std::string text){
        auto it_from = data.find(from);
        auto it_to = data.find(to);
        if(it_from == data.end() || it_to == data.end())
            throw "fail: Usuario nao existe";
        it_from->second->sendMsg(from, to, text);
    }
    std::string show_All(){
        std::stringstream out;
        out << std::endl;
        for(auto it = data.begin(); it != data.end(); it++){
            out << it->second->toString() << std::endl;
        }
        return out.str();
    }

};


#endif //_REP_H_
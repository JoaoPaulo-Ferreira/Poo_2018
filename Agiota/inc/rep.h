#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <algorithm>
#include <map>

// #ifndef exp_enum
// #define exp_enum
// enum exp{
// 	ID_ALREADY_EXIST = 0,
// 	ADD_TYPE_INVALID
// };
// #endif

template<typename T> class Rep{
    std::map<std::string, T> data;
    public:


    bool exist(std::string key){
        return data.find(key) != data.end();
    }

    void add(std::string key, T elemento){
        if(!exist(key)){
            data[key] = elemento;
        }else
            throw "fail: chave ja existe";
    }

    void del(std::string id){
        for(auto it = data.begin(); it != data.end(); it++){
            if(it->second.Client_ID == id){
                data.erase(it);
            }
        }
    }

    std::string show_All(){
        std::stringstream out;
        for(auto it = data.begin(); it != data.end(); it++){
            out << it->second.toString() << std::endl;
        }
        return out.str();
    }

    auto find(std::string key){
        return data.find(key);
    }

    std::string show(std::string id){
        std::stringstream out;
        int acc;
        if(exist(id))
            throw "fail: cliente não existe";

        for(auto it = data.begin(); it != data.end(); it++){
            if(it->second.Client_ID == id){
                out << it->second.toString() << "\n"/*<< it->second.value*/;
                acc += it->second.value;
            }
        }
        out << "Saldo: " << acc << "\n";
        return out.str();
    }

    
};


#endif
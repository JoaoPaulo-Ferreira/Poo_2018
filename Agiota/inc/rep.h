#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <algorithm>
#include <map>

// #ifndef exp_enum
// #define exp_enum
enum exp{
	C_EXIST = 0,
	T_EXIST,
	ADD_TYPE_INVALID
};
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
            throw C_EXIST;
    }
};


#endif
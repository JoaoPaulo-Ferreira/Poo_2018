#ifndef _USERMSG_H_
#define _USERMSG_H_

#include <iostream>
#include <vector>

class Msg{
public:
    std::string title;
    std::string text;

    Msg();
    Msg(std::string title, std::string text){
        this->title = title;
        this->text = text;
    }
    std::string toString(){
        return "\t[" + this->title + ":" + this->text + "]\n";
    }
};

class User{
public:
    std::string name;
    std::vector<Msg> inbox;
    User();
    User(std::string);
    virtual std::string readMsg() = 0;
    virtual void sendMsg(std::string, std::string, std::string) = 0;
    virtual std::string toString() = 0;
    virtual void tie(void * user) = 0;
};

#endif //_USERMSG_H_
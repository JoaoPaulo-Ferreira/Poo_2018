/*class User{
    std::string name;
    std::vector<Msg> inbox;
public:
    User();
    User(std::string);
    virtual std::string readMsg() = 0;
    virtual void sendMsg(std::string, std::string) = 0;
    virtual std::string toString() = 0;
};*/
#include<iostream>
#include "user.h"

User::User(){}

User::User(std::string name){
    this->name = name;
}

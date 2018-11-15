#ifndef _DOCTOR_H_
#define _DOCTOR_H_
#include <sstream>
#include <iostream>
#include <vector>
#include "patient.h"


// class User{
//     std::string name;
//     std::vector<Msg> inbox;
// public:
//     User();
//     User(std::string);
//     virtual std::string readMsg() = 0;
//     virtual void sendMsg(std::string, std::string) = 0;
//     virtual std::string toString() = 0;
// };

class Doctor : public User{
public:
    std::string spec;
    std::vector<Patient *> p_list;
    Doctor(std::string, std::string);
    virtual ~Doctor();
    std::string readMsg();
    void sendMsg(std::string, std::string);
    void sendMsg(std::string, std::string, std::string);
    std::string getPats(size_t);
    std::string toString();
    virtual void tie(void *);

};




#endif //_DOCTOR_H_
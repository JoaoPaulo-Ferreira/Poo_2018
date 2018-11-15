#ifndef _PATIENT_H_
#define _PATIENT_H_
#include "user.h"
#include <vector>
#include <iostream>
#include <sstream>

class Doctor;

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

class Patient : public User{
public:
    std::string diag;
    std::vector<Doctor *> d_list;
    Patient(std::string, std::string);
    virtual ~Patient();
    virtual std::string readMsg();
    void sendMsg(std::string, std::string);
    void sendMsg(std::string, std::string, std::string);
    std::string getDocs(size_t);
    std::string toString();
    virtual void tie(void *);

friend class Doctor;
};




#endif //_PATIENT_H_
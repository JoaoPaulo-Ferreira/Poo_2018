#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include "sistema.h"
#include <sstream>

class Controller{
	Sistema sistema;
public:
	Controller();
	std::string shell(std::string);
	void exec();


};
#endif // CONTROLLER_H

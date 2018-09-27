#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <sstream>
#include "sistema.h"

class Controller{
	Sistema sistema;
public:
	Controller();
	std::string shell(std::string);
	void exec();
	void add_func(std::string);
};
#endif // CONTROLLER_H
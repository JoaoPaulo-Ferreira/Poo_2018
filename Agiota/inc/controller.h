#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <sstream>
#include "sistema.h"
#include <cstdlib>

class Controller{
	Sistema sistema;
public:
	Controller();
	std::string shell(std::string);
	void exec();
	std::string show_func(std::string);
	void add_func(std::string);
	void mercenario(std::string);
};
#endif // CONTROLLER_H
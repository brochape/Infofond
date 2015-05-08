#include "Solver.hpp"
#include "Parser.cpp"
#include "Data.cpp"
#include <iostream>
#include <String>

class ScheduleSolver
{
public:
	ScheduleSolver(){

	}

	void solve() {
		std::string s = std::string("plop");
		Parser p = Parser(s); 
		Data d = p.parse();
		std::cout << d.getT() << std::endl;
	}

	~ScheduleSolver(){

	}

	/* data */
};
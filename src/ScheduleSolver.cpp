#include "ScheduleSolver.hpp"
#include "Solver.hpp"
#include "Parser.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>

ScheduleSolver::ScheduleSolver(){ 
}

void ScheduleSolver::solve(std::string fileName) {
	Parser p = Parser(fileName); 
	Data d = p.parse();
	std::cout << d.getT() << std::endl;
}

ScheduleSolver::~ScheduleSolver(){

}
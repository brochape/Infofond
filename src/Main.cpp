#include <iostream>
#include <string>

#include "ScheduleSolver.hpp"

using namespace std;

int main() {
	std::string str = std::string("data/example-inputs.txt");
	ScheduleSolver s = ScheduleSolver();
	s.solve(str);
}

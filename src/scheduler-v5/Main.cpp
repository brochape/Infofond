#include <iostream>
#include <string>

#include "ScheduleSolver.hpp"

using namespace std;

int main() {
	std::string str = std::string("data/example-inputs5.txt");
	ScheduleSolver s(str);
	s.solve();
	s.solve();
	return 0;
}

#include <iostream>
#include <string>

#include "ScheduleSolver.hpp"

using namespace std;

int main(int argc, char** argv) {
    std::string str = std::string(argv[1]);
	ScheduleSolver s(str);
	s.solve();
	s.solve();
	s.solve();
	return 0;
}

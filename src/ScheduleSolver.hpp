#ifndef SCHEDULE_SOLVER_HPP
#define SCHEDULE_SOLVER_HPP

#include "Parser.hpp"

#include <string>

class ScheduleSolver {
public:
	ScheduleSolver(std::string fileName);

	void solve();

	~ScheduleSolver();

private:
	Parser p;

};

#endif // SCHEDULE_SOLVER_HPP
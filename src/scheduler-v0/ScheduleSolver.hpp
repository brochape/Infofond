#ifndef SCHEDULE_SOLVER_HPP
#define SCHEDULE_SOLVER_HPP

#include "Parser.hpp"

#include <string>

class ScheduleSolver {
public:
	ScheduleSolver();

	void solve();
	std::vector<int> countStudents(int X, std::vector<std::vector<int>> a);

	~ScheduleSolver();

private:
	Parser parser;

};

#endif // SCHEDULE_SOLVER_HPP
#ifndef SCHEDULE_SOLVER_HPP
#define SCHEDULE_SOLVER_HPP

#include <string>

class ScheduleSolver {
public:
	ScheduleSolver();

	void solve(std::string fileName);

	~ScheduleSolver();

};

#endif // SCHEDULE_SOLVER_HPP
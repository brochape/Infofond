#ifndef SCHEDULE_SOLVER_HPP
#define SCHEDULE_SOLVER_HPP

class ScheduleSolver {
public:
	ScheduleSolver(std::string fileName);

	void solve();

	~ScheduleSolver();

};

#endif // SCHEDULE_SOLVER_HPP
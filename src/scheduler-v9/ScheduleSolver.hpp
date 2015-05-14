#ifndef SCHEDULE_SOLVER_HPP
#define SCHEDULE_SOLVER_HPP

#include "Parser.hpp"
#include "../minisat/Solver.hpp"

#include <string>
#include <vector>

class ScheduleSolver {
public:
	ScheduleSolver(std::string fileName);

	void solve();
	std::vector<int> countStudents(int X, std::vector<std::vector<int>> a);
	void addConstraint(Solver* sol,vec<Lit>* lits, Data d, int t, int s, int x);


	~ScheduleSolver();

private:

	Parser parser;
	std::vector< std::vector< std::vector <int> > > prop;

};

#endif // SCHEDULE_SOLVER_HPP
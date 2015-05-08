#ifndef __SUDOKU_HPP
#define __SUDOKU_HPP 

#include <iostream>
#include <cmath>
#include "Solver.hpp"

using namespace std;

// N: size of small squares
template<int N>
class Sudoku {
public:
	Sudoku();
	~Sudoku();
	
	void solve();

	template<int X>
	friend istream &operator>>(istream &in, Sudoku<X> &s);

	template<int X>
	friend ostream &operator<<(ostream &out, const Sudoku<X> &s);

private:
	void addNewVar(Solver &s);
	void generateGridConstraints(Solver &s);
	void generateGlobalConstraints(Solver &s);
	void generateRowConstraints(Solver &s);
	void generateColumnConstraints(Solver &s);
	void generateSquareConstraints(Solver &s);

	void parseSolution(const Solver &s);

	string grid[N*N][N*N];
	int prop[N*N][N*N][N*N+1];
	vec<Lit> lits;
};

template<int X>
istream &operator>>(istream &in, Sudoku<X> &s);

template<int X>
ostream &operator<<(ostream &out, const Sudoku<X> &s);
	
#include "Sudoku.cpp"
	   
#endif

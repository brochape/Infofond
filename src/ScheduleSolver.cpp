#include "ScheduleSolver.hpp"
#include "Solver.hpp"
#include "Parser.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>
#include <cmath>

ScheduleSolver::ScheduleSolver(std::string fileName) : p(fileName) { 

}

void ScheduleSolver::solve() {
	Data d = this->p.parse();
	std::cout << d.getT() << " " << d.getS() << " " << d.getX() << std::endl;

	Solver sol;
	int prop[d.getX()][d.getT()][d.getS()];

	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				prop[x][t][s] = sol.newVar();
			}
		}
	}

	// Contrainte d'unicité sur les examen, le temps et les salles
	// -> les examens ne se produisent pas deux fois (dans le temps et l'espace)
	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				for (int k = 0; k < d.getX(); ++k) {
					if (k!=x) {
						sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[k][t][s]));
					}
				}
				for (int k = 0; k < d.getT(); ++k) {
					if (k!=t) {
						sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[x][k][s]));
					}
				}
				for (int k = 0; k < d.getS(); ++k) {
					if (k!=s) {
						sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[x][t][k]));
					}
				}
			}
		}
	}

	// Contrainte d'existence
	// -> Il faut que chaque examen soit planifié au moins une fois
	for (int x = 0; x < d.getX(); ++x) {
		vec<Lit> lits;
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				lits.push(Lit(prop[x][t][s]));
			}
		}
		sol.addClause(lits);
	}

	sol.solve();

}

ScheduleSolver::~ScheduleSolver(){

}
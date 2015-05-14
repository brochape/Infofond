#include "ScheduleSolver.hpp"
#include "../minisat/Solver.hpp"
#include "Parser.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

ScheduleSolver::ScheduleSolver(std::string fileName) : parser(fileName) { 

}

void ScheduleSolver::solve() {
	Data d = this->parser.parse();

	d.print();

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

	for (int x1 = 0; x1 < d.getX(); ++x1) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (t+d.getD()[x1]-1<d.getT()) {
					for (int dt = 1; dt < d.getD()[x1]; ++dt) {
						for (int x2 = 0; x2 < d.getX(); ++x2) {
							std::cout << "not " << x1 << " " << t << " " << s << " or not " << x2 << " " << t+dt << " " << s << std::endl;
							sol.addBinary(~Lit(prop[x1][t][s]),~Lit(prop[x2][t+dt][s]));
						}
					}
				}
			}
		}
	}

	// // Contrainte de la limitation de place dans les salles
	// // -> Un examen ou il y a x personnes ne peut pas avoir lieu dans une salle des n places si n<x
	// for (int x = 0; x < d.getX(); ++x) {
	// 	for (int t = 0; t < d.getT(); ++t) {
	// 		for (int s = 0; s < d.getS(); ++s) {
	// 			if (d.getV()[x]>d.getC()[s]) {
	// 				sol.addUnit(~Lit(prop[x][t][s]));
	// 			}
	// 		}
	// 	}
	// }

	// // Contrainte de la résolution des conflit horraire pour un étudiant
	// // -> Un étudiant ne peut pas avoir 2 examens en même temps
	// for (int e = 0; e < d.getE(); ++e) {
	// 	for (int x = 0; x < d.getA()[e].size(); ++x) {
	// 		for (int y = 0; y < d.getA()[e].size(); ++y) {
	// 			if (x!=y) {
	// 				for (int t = 0; t < d.getT(); ++t) {
	// 					for (int s = 0; s < d.getS(); ++s) {
	// 						for (int s2 = 0; s2 < d.getS(); ++s2) {
	// 							sol.addBinary(~Lit(prop[d.getA()[e][x]-1][t][s]),~Lit(prop[d.getA()[e][y]-1][t][s2]));
	// 						}
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// // Contrainte de la résolution des conflit horraire pour un professeur
	// // -> Un professeur ne peut pas surveiller 2 examens en même temps
	// for (int p = 0; p < d.getP(); ++p) {
	// 	for (int x = 0; x < d.getB()[p].size(); ++x) {
	// 		for (int y = 0; y < d.getB()[p].size(); ++y) {
	// 			if (x!=y) {
	// 				for (int t = 0; t < d.getT(); ++t) {
	// 					for (int s = 0; s < d.getS(); ++s) {
	// 						for (int s2 = 0; s2 < d.getS(); ++s2) {
	// 							sol.addBinary(~Lit(prop[d.getB()[p][x]-1][t][s]),~Lit(prop[d.getB()[p][y]-1][t][s2]));
	// 						}
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	sol.solve();

	// print de l'output
	if (sol.okay()) {
		for (int x = 0; x < d.getX(); ++x) {
			for (int t = 0; t < d.getT(); ++t) {
				for (int s = 0; s < d.getS(); ++s) {
					if (sol.model[prop[x][t][s]]==l_True) {
						std::cout << "L'examen " << x << " se tiendra pendant la période " << t << " dans la salle " << s << std::endl;
					}
				}
			}
		}
	}
	else{
		std::cout << "Ce problème n'a pas de solution."<<std::endl;
	}

}

ScheduleSolver::~ScheduleSolver(){

}
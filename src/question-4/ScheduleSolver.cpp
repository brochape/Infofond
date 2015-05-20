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

	// C1,C2,C3.1 : Contrainte d'unicité sur les examens, le temps et les salles
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

	// C3.2 : Contrainte d'existence
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

	// C4 : Contrainte de la taille limitée des salles
	// -> Un examen, que x personnes doit passer, ne peut pas avoir lieu dans une salle avec n places si n<x
	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (d.getV()[x]>d.getC()[s]) {
					sol.addUnit(~Lit(prop[x][t][s]));
				}
			}
		}
	}

	// C5 : Contrainte d'interdiction des conflits horraires pour un étudiant
	// -> Un étudiant ne peut pas passer 2 examens en même temps
	for (int e = 0; e < d.getE(); ++e) {
		for (int i = 0; i < d.getA()[e].size(); ++i) {
			int x(d.getA()[e][i]-1); // x = l'ID d'un examen
			for (int j = 0; j < d.getA()[e].size(); ++j) {
				int y(d.getA()[e][j]-1); // y = l'ID d'un examen
				if (x!=y) {
					for (int t = 0; t < d.getT(); ++t) {
						for (int s = 0; s < d.getS(); ++s) {
							for (int s2 = 0; s2 < d.getS(); ++s2) {
								sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[y][t][s2]));
							}
						}
					}
				}
			}
		}
	}

	// C6 : Contrainte d'interdiction des conflits horraires pour un professeur
	// -> Un professeur ne peut pas surveiller 2 examens en même temps
	for (int p = 0; p < d.getP(); ++p) {
		for (int i = 0; i < d.getB()[p].size(); ++i) {
			int x(d.getB()[p][i]-1); // x = l'ID d'un examen
			for (int j = 0; j < d.getB()[p].size(); ++j) {
				int y(d.getB()[p][j]-1); // y = l'ID d'un examen
				if (x!=y) {
					for (int t = 0; t < d.getT(); ++t) {
						for (int s = 0; s < d.getS(); ++s) {
							for (int s2 = 0; s2 < d.getS(); ++s2) {
								sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[y][t][s2]));
							}
						}
					}
				}
			}
		}
	}

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
		std::cout << "S\\T\t";
		for (int t = 0; t < d.getT(); ++t) { std::cout << t << '\t' ; }
		std::cout << std::endl;
		for (int s = 0; s < d.getS(); ++s) {
			std::cout << s << '\t' ;
			for (int t = 0; t < d.getT(); ++t) {
				for (int x = 0; x < d.getX(); ++x) {
					if (sol.model[prop[x][t][s]]==l_True) {
						std::cout << "X" << x ;
					}
				}
				std::cout << '\t' ;
			}
			std::cout << std::endl;
		}

		std::cout<<std::endl;
		std::cout<<"-------------------FORMATED OUTPUT-------------------"<<std::endl;
		std::cout<<std::endl;
		for (int x = 0; x < d.getX(); ++x) {
			for (int t = 0; t < d.getT(); ++t) {
				for (int s = 0; s < d.getS(); ++s) {
					if (sol.model[prop[x][t][s]]==l_True) {
						std::cout << s << "," << t << ";";
					}
				}
			}
		}
		std::cout << std::endl;


	}
	else{
		std::cout << "Ce problème n'a pas de solution."<<std::endl;
		std::cout << 0 << std::endl;
	}

}

ScheduleSolver::~ScheduleSolver(){

}
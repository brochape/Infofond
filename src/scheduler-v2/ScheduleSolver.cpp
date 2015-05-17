#include "ScheduleSolver.hpp"
#include "../minisat/Solver.hpp"
#include "Parser.hpp"
#include "Data.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

ScheduleSolver::ScheduleSolver() : parser() { 

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

	// Contrainte de continuité dans le temps d'un examen
	// -> Un examen peut se dérouler sur plusieurs périodes
	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (t+d.getD()[x]-1<d.getT()) {
					for (int dt = 1; dt < d.getD()[x]; ++dt) {
						for (int x2 = 0; x2 < d.getX(); ++x2) {
							sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[x2][t+dt][s]));
						}
					}
				}
			}
		}
	}

	// Contrainte d'interdiction de sortie des bornes horraires
	// -> un examen qui dure n périodes ne peut pas être placé dans [T-n+1 ,T-1] sans sortir de l'horraire
	for (int x = 0; x < d.getX(); ++x) {
		for (int s = 0; s < d.getS(); ++s) {
			for (int t = d.getT()-d.getD()[x]+1; t < d.getT(); ++t) {
				sol.addUnit(~Lit(prop[x][t][s]));
			}
		}
	}

	// Contrainte de la taille limitée des salles
	// -> Un examen, que x personnes doit passer, ne peut pas avoir lieu dans une salle avec n places si n<x
	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (d.getV()[x]>d.getC()[s]) {
					sol.addUnit(~Lit(prop[x][t][s]));
				}
			}
		}
	};

	// Contrainte d'interdiction des conflits horraires pour un étudiant
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
								for (int t2 = t-d.getD()[y]+1; t2 <= t+d.getD()[x]-1; ++t2) {
									if ((t2>=0) && (t2<d.getT())) {
										sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[y][t2][s2]));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Contrainte d'interdiction des conflits horraires pour un professeur
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
								for (int t2 = t-d.getD()[y]+1; t2 <= t+d.getD()[x]-1; ++t2) {
									if ((t2>=0) && (t2<d.getT())) {
										sol.addBinary(~Lit(prop[x][t][s]),~Lit(prop[y][t2][s2]));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Contrainte d'interdiction de placer un examen pendant un intervalle non disponible
	// -> aucun examen ne peut commencer dans cet intervalle de temps, ni déborder dans cet intervalle de temps
	for (int i = 0; i < d.getI().size(); ++i) {
		int d1(d.getI()[i][0]);
		int d2(d.getI()[i][1]);
		for (int x = 0; x < d.getX(); ++x) {
			for (int s = 0; s < d.getS(); ++s) {
				for (int t = d1; t < d2+1; ++t) {
					sol.addUnit(~Lit(prop[x][t][s]));
				}
			}
		}
		for (int x = 0; x < d.getX(); ++x) {
			for (int s = 0; s < d.getS(); ++s) {
				for (int t = d1-d.getD()[x]+1; t < d1; ++t) {
					if (t>=0) {
						sol.addUnit(~Lit(prop[x][t][s]));
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
						for (int i = 0; i < d.getD()[x]-1; ++i){
							std::cout << "X" << x << '\t';
						}
						t+=d.getD()[x]-1;
						std::cout << "X" << x;
						
					}
				}
				std::cout << '\t' ;
			}
			std::cout << std::endl;
		}
	}
	else{
		std::cout << "Ce problème n'a pas de solution."<<std::endl;
	}

}

ScheduleSolver::~ScheduleSolver(){

}
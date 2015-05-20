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

	// C1, C2, C3.1 : Contrainte d'unicité sur les examen, le temps et les salles
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

	// C4 : Contrainte de la limitation de place dans les salles
	// -> Un examen ou il y a x personnes ne peut pas avoir lieu dans une salle des n places si n<x
	for (int x = 0; x < d.getX(); ++x) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (d.getV()[x]>d.getC()[s]) {
					sol.addUnit(~Lit(prop[x][t][s]));
				}
			}
		}
	};

	// C5.2 : Contrainte de la résolution des conflit horraire pour un étudiant
	// -> Un étudiant ne peut pas avoir 2 examens en même temps
	for (int e = 0; e < d.getE(); ++e) {
		for (int x = 0; x < d.getA()[e].size(); ++x) {
			for (int y = 0; y < d.getA()[e].size(); ++y) {
				if (x!=y) {
					for (int t = 0; t < d.getT(); ++t) {
						for (int s = 0; s < d.getS(); ++s) {
							for (int s2 = 0; s2 < d.getS(); ++s2) {
								for (int dt = t-d.getD()[d.getA()[e][y]-1]+1; dt <= t+d.getD()[d.getA()[e][x]-1]-1; ++dt) {
									if ((dt>=0) && (dt<d.getT())) {
										sol.addBinary(~Lit(prop[d.getA()[e][x]-1][t][s]),~Lit(prop[d.getA()[e][y]-1][dt][s2]));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// C6.2 : Contrainte de la résolution des conflit horraire pour un professeur
	// -> Un professeur ne peut pas surveiller 2 examens en même temps
	for (int p = 0; p < d.getP(); ++p) {
		for (int x = 0; x < d.getB()[p].size(); ++x) {
			for (int y = 0; y < d.getB()[p].size(); ++y) {
				if (x!=y) {
					for (int t = 0; t < d.getT(); ++t) {
						for (int s = 0; s < d.getS(); ++s) {
							for (int s2 = 0; s2 < d.getS(); ++s2) {
								for (int dt = t-d.getD()[d.getB()[p][y]-1]+1; dt <= t+d.getD()[d.getB()[p][x]-1]-1; ++dt) {
									if ((dt>=0) && (dt<d.getT())) {
										sol.addBinary(~Lit(prop[d.getB()[p][x]-1][t][s]),~Lit(prop[d.getB()[p][y]-1][dt][s2]));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// C7.1 : Contrainte de continuité dans le temps d'un examen
	// -> Un examen peut se dérouler sur plusieurs périodes
	for (int x1 = 0; x1 < d.getX(); ++x1) {
		for (int t = 0; t < d.getT(); ++t) {
			for (int s = 0; s < d.getS(); ++s) {
				if (t+d.getD()[x1]-1<d.getT()) {
					for (int dt = 1; dt < d.getD()[x1]; ++dt) {
						for (int x2 = 0; x2 < d.getX(); ++x2) {
							sol.addBinary(~Lit(prop[x1][t][s]),~Lit(prop[x2][t+dt][s]));
						}
					}
				}
			}
		}
	}

	// C7.2 : Contrainte d'interdiction de sortie des bornes horraires
	// -> un examen qui dure n périodes ne peut pas être placé dans [T-n+1 ,T-1] sans sortir de l'horraire
	for (int x = 0; x < d.getX(); ++x) {
		for (int s = 0; s < d.getS(); ++s) {
			for (int t = d.getT()-d.getD()[x]+1; t < d.getT(); ++t) {
				sol.addUnit(~Lit(prop[x][t][s]));
			}
		}
	}

	// C8 : Contrainte d'interdiction de placer un examen pendant un intervalle non disponible
	// -> aucun examen ne peut commencer dans cet intervalle de temps, ni déborder dans cet intervalle de temps
	for (int i = 0; i < d.getI().size(); ++i) {
		int d1(d.getI()[i][0]);
		int d2(d.getI()[i][1]);
		for (int x = 0; x < d.getX(); ++x) {
			for (int s = 0; s < d.getS(); ++s) {
				for (int t = d1-d.getD()[x]+1; t < d2+1; ++t) {
					if (t>=0) {
						sol.addUnit(~Lit(prop[x][t][s]));
					}
				}
			}
		}
	}

	// C10 : Contrainte d'interdiction de changement de salle sans pause entre chaque pair examens d'un étutudiant
	for (int e = 0; e < d.getE(); ++e) {
		for (int x = 0; x < d.getA()[e].size(); ++x) {
			for (int y = 0; y < d.getA()[e].size(); ++y) {
				if (x!=y) {
					for (int t = 0; t < d.getT(); ++t) {
						for (int s = 0; s < d.getS(); ++s) {
							for (int s2 = 0; s2 < d.getS(); ++s2) {
								int dt(d.getD()[d.getA()[e][x]-1]);
								if ((s!=s2) && (t+dt<d.getT())) {
									sol.addBinary(~Lit(prop[d.getA()[e][x]-1][t][s]),~Lit(prop[d.getA()[e][y]-1][t+dt][s2]));
								}
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
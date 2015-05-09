#include "Data.hpp"
#include <iostream>

Data::Data(int T, int S, std::vector<int> c, int E, int P, int X, std::vector<std::vector<int>> a, std::vector<std::vector<int>> b) :
		T(T),
		S(S),
		c(c),
		E(E),
		P(P),
		X(X),
		a(a),
		b(b),
		v(countStudents(X,a))
{}

void Data::print() {
	std::cout << "Examens: " << this->getX() << "\nPériodes: " << this->getT() << "\nSalles: " << this->getS() << std::endl;
	std::cout << "Taille des salles: " ;
	for (int s = 0; s < this->getS(); ++s) {
		std::cout << this->getC()[s] << ", ";
	}
	std::cout << std::endl;
	std::cout << "Nombre d'inscrit par examen: " ;
	for (int x = 0; x < this->getX(); ++x) {
		std::cout << this->getV()[x] << ", ";
	}
	std::cout << std::endl;
	 
}

std::vector<int> Data::countStudents(int X, std::vector<std::vector<int>> a) {
	std::vector<int> res(X);
	for (int e = 0; e < a.size(); ++e) {
		for (int x = 0; x < a[e].size(); ++x) {
			++res[a[e][x]-1];
		}
	}
	return res;
}

Data::~Data() {
}
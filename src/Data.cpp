#include "Data.hpp"

Data::Data(int T, int S, int* c, int E, int P, int X, int* a, int* b) :
		T(T),
		S(S),
		c(c),
		E(E),
		P(P),
		X(X),
		a(a),
		b(b)
{}

Data::~Data() {
	delete[] c;
	delete[] a;
	delete[] b;
}
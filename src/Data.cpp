#include "Data.hpp"

Data::Data(int T, int S, std::vector<int> c, int E, int P, int X, std::vector<std::vector<int>> a, std::vector<std::vector<int>> b) :
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
}
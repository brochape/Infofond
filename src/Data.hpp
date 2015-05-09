#ifndef DATA_HPP
#define DATA_HPP

#include <vector>

class Data {
public:
	Data(){}
	Data(int T, int S, std::vector<int> c, int E, int P, int X, std::vector<std::vector<int>> a, std::vector<std::vector<int>> b );

	int getT() { return this->T; }
	int getS() { return this->S; }
	std::vector<int> getC() { return this->c; }
	int getE() { return this->E; }
	int getP() { return this->P; }
	int getX() { return this->X; }
	std::vector<std::vector<int>> getA() { return this->a; }
	std::vector<std::vector<int>> getB() { return this->b; }

	~Data();

private:
	int T;
	int S;
	std::vector<int> c;
	int E;
	int P;
	int X;
	std::vector<std::vector<int>> a;
	std::vector<std::vector<int>> b;
};

#endif //DATA_HPP
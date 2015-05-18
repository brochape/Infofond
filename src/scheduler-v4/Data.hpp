#ifndef DATA_HPP
#define DATA_HPP

#include <vector>

class Data {
public:
	Data(){}
	Data(int T, int S, std::vector<int> c, int E, int P, int X, std::vector<std::vector<int>> a, std::vector<std::vector<int>> b, std::vector<int> d, int I, std::vector<std::vector<int> > i, int N, std::vector<std::vector<int> >f );

	int getT() { return this->T; }
	int getS() { return this->S; }
	std::vector<int> getC() { return this->c; }
	int getE() { return this->E; }
	int getP() { return this->P; }
	int getX() { return this->X; }
	std::vector<std::vector<int>> getA() { return this->a; }
	std::vector<std::vector<int>> getB() { return this->b; }
	std::vector<int> getV() { return this->v; }
	std::vector<int> getD() { return this->d; }
	std::vector<std::vector<int> > getI() { return this->i; }
	int getN() { return this->N; }
	std::vector<std::vector<int> > getF() { return this->f; }

	void print();

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
	std::vector<int> v;
	std::vector<int> d;
	int I;
	std::vector<std::vector<int> > i;
	int N;
	std::vector<std::vector<int> > f;

	std::vector<int> countStudents(int X, std::vector<std::vector<int>> a);

};

#endif //DATA_HPP
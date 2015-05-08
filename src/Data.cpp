
class Data
{
public:
	Data(int T, int S, int* c, int E, int P, int X, int* a, int* b ) {
		this.T = T;
		this.S = S;
		this.c = c;
		this.E = E;
		this.P = P;
		this.X = X;
		this.a = a; 
		this.b = b;
	}

	int getT() { return this.T; }
	int getS() { return this.S; }
	int* getC() { return this.c; }
	int getE() { return this.E; }
	int getP() { return this.P; }
	int getX() { return this.X; }
	int* getA() { return this.a; }
	int* getB() { return this.b; }

	~Data();
private:
	int T;
	int S;
	int* c;
	int E;
	int P;
	int X;
	int* a;
	int* b;
};
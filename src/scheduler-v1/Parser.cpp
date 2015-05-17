
#include "Parser.hpp"
#include "Data.hpp"
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Parser::Parser() {
	std::cin >> line;
}

Data Parser::parse(){
	if(line != ""){ 
		std::istringstream iss(line);
		std::string token;
		// T = nombre de périodes
		getline(iss,token,';');
		int T(atoi(token.c_str()));
		// S = nombre de salles
		getline(iss,token,';');
		int S(atoi(token.c_str()));
		// c = liste des tailles des salles
		std::vector<int> c;
		for (int i = 0; i < S; ++i) {
			getline(iss,token,';');
			c.push_back(atoi(token.c_str()));
		}
		// E = nombre d'étudiants
		getline(iss,token,';');
		int E(atoi(token.c_str()));
		// P = nombre de professeurs
		getline(iss,token,';');
		int P(atoi(token.c_str()));
		// X = nombre d'examens
		getline(iss,token,';');
		int X(atoi(token.c_str()));
		// a = liste des examens par étudiant
		std::vector<std::vector<int>> a;
		for (int i = 0; i < E; ++i)
		{
			getline(iss,token,';');
			std::istringstream iss2(token);
			std::string tk;
			std::vector<int> e;
			while (getline(iss2,tk,',')) {
				e.push_back(atoi(tk.c_str()));
			}
			a.push_back(e);
		}
		// b = liste des examens par professeur
		std::vector<std::vector<int>> b;
		for (int i = 0; i < P; ++i)
		{
			getline(iss,token,';');
			std::istringstream iss2(token);
			std::string tk;
			std::vector<int> p;
			while (getline(iss2,tk,',')) {
				p.push_back(atoi(tk.c_str()));
			}
			b.push_back(p);
		}
		// d = liste des taille des examens
		std::vector<int> d;
		for (int i = 0; i < X; ++i) {
			getline(iss,token,';');
			d.push_back(atoi(token.c_str()));
		}
		return Data(T,S,c,E,P,X,a,b,d);
	} else {
		return Data();
	}
}

Parser::~Parser() {
}
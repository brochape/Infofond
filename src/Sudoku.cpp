#ifndef __SUDOKU_CPP

#define __SUDOKU_CPP
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Sudoku.hpp"
#include "Solver.hpp"

using namespace std;

#define FOR(k,lb,ub) for (int k = (lb); (k) <= (ub); (k)++)

template<int N>
inline Sudoku<N>::Sudoku() {
}

template<int N>
inline Sudoku<N>::~Sudoku() {
}

template<int N>
inline istream &operator>>(istream &in, Sudoku<N> &s) {
   FOR(i,0,N*N-1) FOR(j,0,N*N-1) {
      in >> s.grid[i][j];
   }
   return in;
}

template<int N>
inline ostream &operator<<(ostream &out, const Sudoku<N> &s) {
   // print the grid

   FOR(i,0,N*N-1) {
      if (i%N == 0) {
	 FOR(j,1,3*N*N+N){
	    out << "-" ;
	 }
	 out << "|" << endl ;
      }
      FOR(j,0,N*N-1) {
	 if (j%N == 0) { out << "|" ;}
	 out << s.grid[i][j] << " ";
      }
      out << "|" ;
      out << endl;
   }
   FOR(j,1,3*N*N+N){
      out << "-" ;
   }
   out << "|" << endl ;
   return out;
}

/*************************/

template<int N>
inline void Sudoku<N>::addNewVar(Solver &s) {
   // declare new variables
   FOR(i,0,N*N-1) { 
      FOR(j,0,N*N-1) {
	 FOR(v,1,N*N) {
	    prop[i][j][v] = s.newVar() ;
	 }
      }
      
   }
}


template<int N>
inline void Sudoku<N>::generateGlobalConstraints(Solver &s) {
	// There is at least one value in each entry:
	FOR(i,0,N*N-1) FOR(j,0,N*N-1) {
		lits.clear();
		FOR(v,1,N*N) { 
		   lits.push(Lit(prop[i][j][v]));
		   cout << prop[i][j][v] << " ";
		}
		s.addClause(lits);
		cout << "\n" ;
	}
}


template<int N>
inline void Sudoku<N>::generateGridConstraints(Solver &s) {
   // Take prefilled values into account
   FOR(i,0,N*N-1) FOR(j,0,N*N-1) {
      if (grid[i][j] != "-") {
	 s.addUnit(Lit(prop[i][j][atoi((grid[i][j].data()))]));
	 cout << prop[i][j][atoi((grid[i][j].data()))] << endl;
      }
   }
}


template<int N>
inline void Sudoku<N>::generateRowConstraints(Solver &s) {
	// Each value appears at most once in each row:
   FOR(j,0,N*N-1) 
      FOR(v,1,N*N)
         FOR(i,0,N*N-2) 
            FOR(k,i+1,N*N-1) {
                 s.addBinary(~Lit(prop[i][j][v]), ~Lit(prop[k][j][v]));	
                 cout << "-" << prop[i][j][v] << " -" << prop[k][j][v] << endl;
   }
}


template<int N>
inline void Sudoku<N>::generateColumnConstraints(Solver &s) {
	// Each value appears at most once in each column:
   FOR(i,0,N*N-1) 
      FOR(v,1,N*N) 
        FOR(j,0,N*N-2)
      FOR(k,j+1,N*N-1) {
      s.addBinary(~Lit(prop[i][j][v]), ~Lit(prop[i][k][v]));
      cout << "-" << prop[i][j][v] << " -" << prop[i][k][v] << endl;
   }
}



template<int N>
inline void Sudoku<N>::generateSquareConstraints(Solver &s) {
	// Each value appears at most once in each NxN square:
	FOR(k,0,N-1) FOR(l,0,N-1) FOR(v,1,N*N) FOR(dk,0,N-1) FOR(dl,0,N-1) {
	   FOR(dn,dl+1,N-1) {
	      s.addBinary(~Lit(prop[N*k+dk][N*l+dl][v]), ~Lit(prop[N*k+dk][N*l+dn][v]));
	      cout << "-" << prop[N*k+dk][N*l+dl][v] << " -" << prop[N*k+dk][N*l+dn][v] << endl;
	   }

	   FOR(dm,dk+1,N-1) FOR(dn,0,N-1) {
	      s.addBinary(~Lit(prop[N*k+dk][N*l+dl][v]), ~Lit(prop[N*k+dm][N*l+dn][v]));
	      cout << "-" << prop[N*k+dk][N*l+dl][v] << " -" << prop[N*k+dm][N*l+dn][v] << endl;
	   }
	}
}


template<int N>
inline void Sudoku<N>::parseSolution(const Solver &s) {

   FOR(i,0,N*N-1) {
      FOR(j,0,N*N-1) {
	 FOR(v,1, N*N) {
	    if (s.model[prop[i][j][v]] == l_True) {
	       char s[255];
	       sprintf(s, "%2i", v) ;
	       grid[i][j] = s ;
	    }
	 }
      }
   }
}

template<int N>
inline void Sudoku<N>::solve() {
	Solver s;

	addNewVar(s);
	generateGridConstraints(s);
	generateGlobalConstraints(s);
	generateRowConstraints(s);
	generateColumnConstraints(s);
	generateSquareConstraints(s);

	s.solve();

	if (!s.okay()) 
	   throw logic_error("Unsolvable sudoku instance");

	parseSolution(s);
}

#endif

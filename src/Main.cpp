#include <iostream>

#include "Sudoku.hpp"

using namespace std;

int main() {
   Sudoku<5> s;
   cin >> s;
   cout << s ;
   cout << endl ;
   s.solve();
   cout << s;
}

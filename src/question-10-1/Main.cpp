#include <iostream>
#include <string>

#include "ScheduleSolver.hpp"

using namespace std;

int main(int argc, char** argv) {
   if(argc != 2) {
      cout << "You need to supply the data as an argument to this program."<<endl;
      return -1;
   }
   else{
    	std::string str = std::string(argv[1]);
    	ScheduleSolver s(str);
    	s.solve();
    	s.solve();
    	return 0;
    }
}


#include "Parser.hpp"
#include "Data.hpp"
#include <string>
#include <fstream>

Parser::Parser(std::string fileName) :
	file(ifstream(fileName))
{

}

Data Parser::parse(){
	string line;
  // if (myfile.is_open())
  // {
  //   while ( getline (myfile,line) )
  //   {
  //     cout << line << '\n';
  //   }
  //   myfile.close();
  // }
	int c[] = {1};
	return Data(1,1,c,1,1,1,c,c);
}

Parser::~Parser() {
	this->file.close();
}
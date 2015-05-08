
#include "Parser.hpp"
#include "Data.hpp"
#include <string>

Parser::Parser(std::string fileName) :
	fileName(fileName)
{}

Data Parser::parse(){
	int c[] = {1};
	return Data(1,1,c,1,1,1,c,c);
}

Parser::~Parser() {}
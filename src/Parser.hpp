#ifndef PARSER_HPP
#define PARSER_HPP

#include "Data.hpp"

#include <string>
#include <fstream>

class Parser {
public:
	Parser(std::string fileName);

	Data parse();

	~Parser();

private:
	ifstream file;
};

#endif // DATA_HPP
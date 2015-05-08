#ifndef PARSER_HPP
#define PARSER_HPP

#include "Data.hpp"

#include <string>

class Parser {
public:
	Parser(std::string fileName);

	Data parse();

	~Parser();

private:
	std::string fileName;
};

#endif // DATA_HPP
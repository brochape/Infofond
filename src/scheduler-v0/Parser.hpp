#ifndef PARSER_HPP
#define PARSER_HPP

#include "Data.hpp"

#include <string>
#include <fstream>

class Parser {
public:
	Parser();

	Data parse();

	~Parser();
private:
    std::string line;
};

#endif // DATA_HPP
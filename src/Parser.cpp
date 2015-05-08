#include <String>
#include "Data.cpp"

class Parser {
public:
	Parser(std::string fileName) {
		this->fileName = fileName;
	}

	Data parse(){
		int c[] = {1};
		return Data(1,1,c,1,1,1,c,c);
	}

	~Parser();

private:
	std::string fileName;
};
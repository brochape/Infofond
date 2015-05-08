#include <Strings>
#include "Data.cpp"

class Parser
{
public:
	Parser(String fileName) {
		this.fileName = fileName;
	}

	Data parse(){
		return Data(1,1,[1],1,1,1,[1],[1])
	}

	~Parser();

private:
	String fileName;
};
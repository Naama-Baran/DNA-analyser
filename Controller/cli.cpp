#include <cstring>
#include "cli.h"


//=================AUXILARY FUNCTIONS====================

inline static std::vector<std::string> split(std::string& str)
{
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> vec;
	current = strtok(cstr," ");
	
	while (current!=NULL)
	{
		vec.push_back(current);
		current=strtok(NULL," ");
	}
	return vec;
}


//===============END AUXILARY FUNCTIONS==================

std::vector<std::string> CLI::vecRead()
{
	std::string str = m_reader->read();
	std::vector<std::string> vec = split(str);
	return vec;
}


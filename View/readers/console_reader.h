#ifndef __CONSOLE_READER__
#define __CONSOLE_READER__

#include <iostream>
#include "../i_reader.h"

class ConsoleReader: public IReader
{
public:
	/*virtual*/std::string read();
};

inline std::string ConsoleReader::read()
{
	std::string str;
	getline(std::cin, str);
	return str;
}

#endif //__CONSOLE_READER__

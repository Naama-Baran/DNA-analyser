#ifndef OPEN_FILE_FAILED_H
#define OPEN_FILE_FAILED_H
#include <stdexcept>
class OpenFileFailed: public std::runtime_error
{
public:
	OpenFileFailed():std::runtime_error(""){};
	
	virtual const char* what() const throw()
	{
		return "open file was failed";
	}
};
#endif
